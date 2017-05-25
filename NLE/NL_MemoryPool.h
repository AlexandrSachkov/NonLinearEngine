#pragma once

#define TBB_PREVIEW_MEMORY_POOL 1
#include "tbb/memory_pool.h"
#include "tbb/scalable_allocator.h"

namespace NLE
{
	namespace MEMORY
	{
		template<size_t S>
		struct Page
		{
			char data[S];
		};

		template<size_t S>
		class MemoryPool
		{
		public:
			MemoryPool() {};
			~MemoryPool() 
			{
				freeAll();
			};

			void* allocate()
			{
				tbb::scalable_allocator<Page<S>> allocator;
				return _pool.malloc(1);
			}
			void free(void* ptr)
			{
				_pool.free(ptr);
			}
			void freeAll()
			{
				_pool.recycle();
			}

		private:
			tbb::memory_pool<tbb::scalable_allocator<Page<S>>> _pool;
		};
	}

}