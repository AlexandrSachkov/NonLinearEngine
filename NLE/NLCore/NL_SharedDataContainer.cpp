//#ifdef NL_SHARED_DATA_CONTAINER_H_

#include "NL_SharedDataContainer.h"

//#include "NL_DataContainer.h"
#include "NL_DataDistributor.h"

#include <cassert>

namespace NLE
{
	namespace Core
	{
		SharedDataContainer::SharedDataContainer(DataDistributor* distributor, AccessType accessType, uint_fast32_t initSize) :
			_distributor(distributor),
			_accessType(accessType),
			_data(),
			_changesPool(),
			_changes(_changesPool),
			_asyncChangesPool(),
			_asyncChanges(_asyncChangesPool)
		{
			_data.reserve(initSize);
			_changes.reserve(initSize / 4);
		}

		SharedDataContainer::~SharedDataContainer()
		{
			_data.clear();
			_changes.clear();
			_changesPool.recycle();
		}

		inline AccessType SharedDataContainer::getAccessType()
		{
			return _accessType;
		}

		inline uint_fast32_t SharedDataContainer::getChange(uint_fast32_t index)
		{
			return _changes[index];
		}

		inline uint_fast32_t SharedDataContainer::getNumChanges()
		{
			return _changes.size();
		}

		inline void SharedDataContainer::add(double data)
		{
			_distributor->requestAdd(data);	
		}

		inline void SharedDataContainer::remove(uint_fast32_t index)
		{
			_distributor->requestRemove(index);	
		}

		inline void SharedDataContainer::modify(uint_fast32_t index, double data)
		{
			assert(_accessType == AccessType::READ_WRITE);
			_data[index] = data;
			_changes.push_back(index);		
		}

		inline uint_fast32_t SharedDataContainer::size()
		{
			return _data.size();
		}

		inline double& SharedDataContainer::get(uint_fast32_t index)
		{
			return _data[index];
		}
		
		void SharedDataContainer::local_remove(uint_fast32_t index)
		{
			uint_fast8_t size = _data.size();
			if (index < size)
			{
				uint_fast8_t lastOccupied = size - 1;
				if (index != lastOccupied)
				{
					_data[index] = _data[lastOccupied];
				}
				_data.pop_back();
			}
		}

		void SharedDataContainer::applyUpdates()
		{
			assert(_accessType == AccessType::READ_ONLY);

			std::pair<ChangeType, Change> pair;
			while(_asyncChanges.try_pop(pair))
			{
				switch(pair.first)
				{
				case ChangeType::ADD:
					_data.push_back(pair.second._data);
					break;
				case ChangeType::REMOVE:
					local_remove(pair.second._index);
					break;
				case ChangeType::MODIFY:
					_data[pair.second._index] = pair.second._data;
					break;
				default:
					break;
				}
			}

		}


		//===================================================================================

		void SharedDataContainer::distributor_add(double data)
		{
			if(_accessType == AccessType::READ_WRITE)
			{
				_data.push_back(data);
			}
			else
			{
				_asyncChanges.push(std::pair<ChangeType, Change>(ChangeType::ADD, {data}));
			}			
		}

		void SharedDataContainer::distributor_remove(uint_fast32_t index)
		{
			if (_accessType == AccessType::READ_WRITE)
			{
				local_remove(index);
			}
			else
			{
				_asyncChanges.push(std::pair<ChangeType, Change>(ChangeType::REMOVE, {index}));
			}
		}

		void SharedDataContainer::distributor_modify(uint_fast32_t index, double data)
		{
			if (_accessType == AccessType::READ_WRITE)
			{
				_data[index] = data;
			}
			else
			{
				_asyncChanges.push(std::pair<ChangeType, Change>(ChangeType::MODIFY, {index, data}));
			}			
		}
	}
}

//#endif