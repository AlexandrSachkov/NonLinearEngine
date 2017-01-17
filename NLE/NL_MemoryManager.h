#pragma once

#include <cstdint>

namespace NLE
{
	namespace MEMORY
	{
		template<typename T>
		class MemPtr
		{
		public:
			MemPtr(T* data, uint_fast32_t poolId) :
				_data(data),
				_poolId(poolId)
			{
			}

			T& get()
			{
				return *_data;
			}

			uint_fast32_t getPoolId()
			{
				return _poolId;
			}
		private:
			T* _data;
			uint_fast32_t _poolId;
		};

		class MemoryManager
		{
		public:
			static MemoryManager& instance()
			{
				if (!_memManager)
				{
					_memManager = new MemoryManager();
				}
				return *_memManager;
			}

			~MemoryManager()
			{

			}

			void release()
			{

			}

			/*template<typename T>
			MemPtr<T> allocate<T>()
			{

			}*/

			/*template<typename T>
			void release<T>(MemPtr<T> ptr)
			{

			}*/

		private:
			MemoryManager()
			{

			}
			MemoryManager(MemoryManager const&) = delete;
			void operator=(MemoryManager const&) = delete;

			static MemoryManager* _memManager;
		};
	}
	
}
