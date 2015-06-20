#ifndef NL_SLAVE_CONTAINER_H_
#define NL_SLAVE_CONTAINER_H_

#include <cstdint>
#include <algorithm>
#include <vector>

#ifndef TBB_PREVIEW_MEMORY_POOL
#define TBB_PREVIEW_MEMORY_POOL 1
#endif

#include "NL_DataRequest.h"

#include "tbb\memory_pool.h"
#include "tbb\scalable_allocator.h"
#include "tbb\concurrent_queue.h"

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			template<typename T>
			class SlaveContainer
			{
				template<typename T>
				friend class MSDistributor;
			public:
				SlaveContainer(size_t initialSize);
				~SlaveContainer();

				size_t size();
				double const& operator[](uint_fast32_t index);
				void modify(uint_fast32_t index, T data);

			private:
				void queueRequest(DistributorRequest request);
				void processRequests();
				void growByOne();
				void localRemove(uint_fast32_t index);

				std::vector<T, tbb::scalable_allocator<T>>& getData();
				std::vector<char, tbb::scalable_allocator<char>>& getChanges();

				std::vector<T, tbb::scalable_allocator<T>> _data;
				std::vector<char, tbb::scalable_allocator<char>> _changes;

				tbb::memory_pool<tbb::scalable_allocator<DistributorRequest>> _requestPool;
				tbb::concurrent_queue<DistributorRequest, tbb::memory_pool_allocator<DistributorRequest>> _requestQueue;

				//used by distributor
				uint_fast32_t updateCycle;
			};
		}
	}
}

#include "NL_SlaveContainer.inl"

#endif