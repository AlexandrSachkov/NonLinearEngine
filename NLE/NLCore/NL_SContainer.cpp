
#include "NL_SContainer.h"

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			SContainer::SContainer(uint_fast32_t dataSize, uint_fast32_t queueSize)
			{
				_data.reserve(dataSize);
				_changes.reserve(queueSize);
			}

			SContainer::~SContainer()
			{
			}

			uint_fast32_t SContainer::size()
			{
				return _data.size();
			}		

			double const& SContainer::operator[](uint_fast32_t index)
			{
				return _data[index];
			}

			void SContainer::modify(uint_fast32_t index, double data)
			{
				_data[index] = data;
				_changes.push_back(index);
			}
			
			std::vector<double, tbb::scalable_allocator<double>>& SContainer::getData()
			{
				return _data;
			}

			std::vector<uint_fast32_t, tbb::scalable_allocator<uint_fast32_t>> const& SContainer::getChanges()
			{
				return _changes;
			}

			void SContainer::clearChanges()
			{
				_changes.clear();
			}
		}
	}
}