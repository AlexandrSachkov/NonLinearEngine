#ifndef NL_DATA_CONTAINER_H_
#define NL_DATA_CONTAINER_H_

#include <algorithm>
#include <vector>
#define TBB_PREVIEW_MEMORY_POOL 1
#include "tbb\memory_pool.h"
#include "tbb\concurrent_queue.h"

#include "NL_DataPacket.h"

namespace NLE
{
	namespace Core
	{
		template<typename T>
		class DataDistributor;

		template<typename T>
		class DataContainer
		{
		public:
			DataContainer(uint_fast8_t sysId, uint_fast8_t initSize);
			~DataContainer();

			void bindDistributor(DataDistributor<T>* distributor);
			void add(T data);
			void remove(uint_fast8_t index);
			void update(uint_fast8_t index, T data);
			uint_fast8_t size();

			T& get(uint_fast8_t index);
			void queuePacket(DataPacket<T> packet);
			void applyUpdates();

		private:		
			uint_fast8_t _sysId;
			tbb::memory_pool<tbb::scalable_allocator<T>> _dataPool;
			std::vector<T, tbb::memory_pool_allocator<T>> _data;
			tbb::concurrent_queue<DataPacket<T>> _updateQueue;

			DataDistributor<T>* _distributor;
		};
	}
}

#include "NL_DataContainer.inl"
#undef TBB_PREVIEW_MEMORY_POOL

#endif