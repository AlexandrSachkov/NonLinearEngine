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
				_distributor(distributor)
			{
				_data.reserve(initialSize);
				_changes.reserve(initialSize);
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

			void MasterContainer::add(double data)
			{
				_data.push_back(data);
				_changes.push_back(0);
				_distributor->queueRequest({ RequestType::ADD, { data } });
			}

			void MasterContainer::remove(uint_fast32_t index)
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

				_distributor->queueRequest({ RequestType::REMOVE, { index } });
			}

			void MasterContainer::itRemove(uint_fast32_t& index)
			{
				remove(index);
				--index;
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