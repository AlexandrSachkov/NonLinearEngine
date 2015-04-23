#ifdef NL_DATA_CONTAINER_H_

#include "NL_DataContainer.h"

namespace NLE
{
	namespace Core
	{
		template<typename T>
		DataContainer<T>::DataContainer() :
			_sysId(-1),
			_dataPool(),
			_data(_dataPool),
			_changesPool(),
			_changes(_changesPool),
			_updateQueue()
		{
		}

		template<typename T>
		DataContainer<T>::~DataContainer()
		{
		}

		template<typename T>
		bool DataContainer<T>::initialize(uint_fast8_t sysId, uint_fast32_t initSize)
		{
			_sysId = sysId;
			_data.reserve(initSize);
			_changes.reserve(initSize / 4);
			return true;
		}

		template<typename T>
		void DataContainer<T>::release()
		{
			_data.clear();
			_dataPool.recycle();
			_changes.clear();
			_changesPool.recycle();
		}

		template<typename T>
		inline void DataContainer<T>::add(T data)
		{
			_data.push_back(data);
		}

		template<typename T>
		void DataContainer<T>::remove(uint_fast32_t index)
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

		template<typename T>
		inline void DataContainer<T>::modify(uint_fast32_t index, T data)
		{
			_data[index] = data;
		}

		template<typename T>
		inline void DataContainer<T>::clear()
		{
			_data.clear();
			_changes.clear();
		}

		template<typename T>
		inline uint_fast32_t DataContainer<T>::size()
		{
			return _data.size();
		}

		template<typename T>
		inline T& DataContainer<T>::get(uint_fast32_t index)
		{
			return _data[index];
		}

		template<typename T>
		inline void DataContainer<T>::queuePacket(DataPacket<T> packet)
		{
			_updateQueue.push(packet);
		}

		template<typename T>
		void DataContainer<T>::applyUpdates()
		{
			DataPacket<T> packet;
			while (_updateQueue.try_pop(packet))
			{
				_data[packet.getItemNumber()] = packet.getData();
			}
		}
	}
}

#endif