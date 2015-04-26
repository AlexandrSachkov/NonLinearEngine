#include "NL_SlaveContainer.h"

#include <cassert>

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			SlaveContainer::SlaveContainer(uint_fast32_t initialSize) :
				_requestQueue(_requestPool)
			{
				_data.resize(initialSize);
				_changes.resize(initialSize, 0);
			}

			SlaveContainer::~SlaveContainer()
			{
			}

			uint_fast32_t SlaveContainer::size()
			{
				return _data.size();
			}

			double const& SlaveContainer::operator[](uint_fast32_t index)
			{
				return _data[index];
			}

			void SlaveContainer::modify(uint_fast32_t index, double data)
			{
				_data[index] = data;
				_changes[index] = 1;
			}

			void SlaveContainer::queueRequest(DistributorRequest request)
			{
				_requestQueue.push(request);
			}

			void SlaveContainer::processRequests()
			{
				DistributorRequest request;
				while (_requestQueue.try_pop(request))
				{
					if (request.type == RequestType::ADD)
					{
						growByOne();
					}
					else
					{
						localRemove(request.index);
					}
				}
			}

			void SlaveContainer::growByOne()
			{
				_data.resize(_data.size() + 1);
				_changes.push_back(0);
			}

			void SlaveContainer::localRemove(uint_fast32_t index)
			{
				uint_fast32_t size = _data.size();
				assert(index < size);

				uint_fast32_t lastOccupied = size - 1;
				if (index != lastOccupied)
				{
					_data[index] = _data[lastOccupied];
					_changes[index] = _changes[lastOccupied];
				}
				_data.pop_back();
				_changes.pop_back();
			}

			std::vector<double, tbb::scalable_allocator<double>>& SlaveContainer::getData()
			{
				return _data;
			}

			std::vector<char, tbb::scalable_allocator<char>>& SlaveContainer::getChanges()
			{
				return _changes;
			}
		}
	}
}