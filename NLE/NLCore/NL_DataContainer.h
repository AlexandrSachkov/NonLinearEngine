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
			DataContainer();
			~DataContainer();

			bool initialize(uint_fast8_t sysId, uint_fast32_t initSize);
			void release();

			void add(T data);
			void remove(uint_fast32_t index);
			void modify(uint_fast32_t index, T data);
			void clear();

			uint_fast32_t size();
			T& get(uint_fast32_t index);

			void queuePacket(DataPacket<T> packet);
			void applyUpdates();

		private:		
			uint_fast8_t _sysId;
			bool _shared;
			tbb::memory_pool<tbb::scalable_allocator<T>> _dataPool;
			std::vector<T, tbb::memory_pool_allocator<T>> _data;

			tbb::memory_pool<tbb::scalable_allocator<uint_fast32_t>> _changesPool;
			std::vector<T, tbb::memory_pool_allocator<uint_fast32_t>> _changes;

			tbb::concurrent_queue<DataPacket<T>> _updateQueue;
		};
	}
}

#include "NL_DataContainer.inl"
#undef TBB_PREVIEW_MEMORY_POOL

#endif