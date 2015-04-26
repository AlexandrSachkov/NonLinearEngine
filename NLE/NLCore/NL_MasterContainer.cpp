#include "NL_MasterContainer.h"

#include "NL_MSDistributor.h"
#include <cassert>

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			MasterContainer::MasterContainer(uint_fast32_t initialSize, MSDistributor* distributor) :
				_distributor(distributor),
				_requestQueue(_requestPool)
			{
				_data.resize(initialSize);
				_changes.resize(initialSize, 0);
			}

			MasterContainer::~MasterContainer()
			{
			}

			uint_fast32_t MasterContainer::size()
			{
				return _data.size();
			}

			double const& MasterContainer::operator[](uint_fast32_t index)
			{
				return _data[index];
			}

			void MasterContainer::modify(uint_fast32_t index, double data)
			{
				_data[index] = data;
				_changes[index] = 1;
			}

			void MasterContainer::requestAdd(double data)
			{
				_distributor->queueRequest({ RequestType::ADD, { data } });
			}

			void MasterContainer::requestRemove(uint_fast32_t index)
			{
				_distributor->queueRequest({ RequestType::REMOVE, { index } });
			}

			void MasterContainer::queueRequest(DistributorRequest request)
			{
				_requestQueue.push(request);
			}

			void MasterContainer::processRequests()
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

			void MasterContainer::growByOne()
			{
				_data.resize(_data.size() + 1);
				_changes.push_back(0);
			}

			void MasterContainer::localRemove(uint_fast32_t index)
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

			std::vector<double, tbb::scalable_allocator<double>>& MasterContainer::getData()
			{
				return _data;
			}

			std::vector<char, tbb::scalable_allocator<char>>& MasterContainer::getChanges()
			{
				return _changes;
			}
		}
	}
}