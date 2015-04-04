#ifndef NL_DATA_CONTAINER_H_
#define NL_DATA_CONTAINER_H_

#include "tbb\concurrent_vector.h"
#include "tbb\concurrent_queue.h"
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
				_maxSize(initSize),
				_currentSize(0),
				_dataPool(),
				_data(_dataPool),
				_removalQueue()
			{
				_data.reserve(initSize);
			}

			~DataContainer()
			{
			}

			void add(T data)
			{
				_data.push_back(data);
				_maxSize = _data.capacity();
				++_currentSize;
			}

			void markForRemoval(uint_fast8_t index)
			{
				_removalQueue.push(index);
			}

			//NOT thread safe
			void maintain()
			{
				uint_fast8_t index;
				while (_removalQueue.try_pop(index))
				{
					std::swap(&_data[_currentSize - 1], &_data[index]);
					--_currentSize;
				}
				_data.shrink_to_fit();
			}

			void update(uint_fast8_t index, T data)
			{
				_data[index] = data;
			}

		private:			
			uint_fast8_t _maxSize;
			uint_fast8_t _currentSize;

			tbb::memory_pool<tbb::scalable_allocator<T>> _dataPool;
			tbb::concurrent_vector<T, tbb::memory_pool_allocator<T>> _data;
			tbb::concurrent_queue<uint_fast8_t> _removalQueue;
		};
	}
}

#undef TBB_PREVIEW_MEMORY_POOL

#endif