#ifndef NL_DATA_CONTAINER_H_
#define NL_DATA_CONTAINER_H_

#include <algorithm>
#include <vector>
#define TBB_PREVIEW_MEMORY_POOL 1
#include "tbb\memory_pool.h"

namespace NLE
{
	namespace Core
	{
		template<typename T>
		class DataContainer
		{
		public:
			DataContainer(uint_fast8_t initSize) :
				_dataPool(),
				_data(_dataPool)
			{
				_data.reserve(initSize);
			}

			~DataContainer()
			{
			}

			void add(T data)
			{
				_data.push_back(data);
			}

			void remove(uint_fast8_t index)
			{
				uint_fast8_t size = _data.size();
				if (index >= size)
					return;

				uint_fast8_t lastOccupied = size - 1;
				if (index != lastOccupied)
				{
					_data[index] = _data[lastOccupied];
				}
				_data.pop_back();
			}

			void update(uint_fast8_t index, T data)
			{
				_data[index] = data;
			}

			T& getData(uint_fast8_t index)
			{
				return _data[index];
			}

		private:			
			tbb::memory_pool<tbb::scalable_allocator<T>> _dataPool;
			std::vector<T, tbb::memory_pool_allocator<T>> _data;
		};
	}
}

#undef TBB_PREVIEW_MEMORY_POOL

#endif