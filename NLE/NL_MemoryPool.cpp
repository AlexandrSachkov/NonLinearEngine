#include "NL_MemoryPool.h"

namespace NLE
{
	namespace MEMORY
	{
		MemoryPool::MemoryPool()
		{
		}

		MemoryPool::~MemoryPool()
		{
			_pool.recycle();
		}

		void* MemoryPool::allocate()
		{
			return _pool.malloc(1);
		}

		void MemoryPool::free(void* ptr)
		{
			_pool.free(ptr);
		}

		void MemoryPool::freeAll()
		{
			_pool.recycle();
		}
	}

}