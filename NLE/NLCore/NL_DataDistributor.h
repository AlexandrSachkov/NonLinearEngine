#ifndef NL_DATA_DISTRIBUTOR_H_
#define NL_DATA_DISTRIBUTOR_H_

#ifndef TBB_PREVIEW_MEMORY_POOL
#define TBB_PREVIEW_MEMORY_POOL 1
#endif

#include "tbb\memory_pool.h"
#include "tbb\concurrent_queue.h"

#include <vector>
#include <unordered_map>

#include "NL_ExecutionDesc.h"
#include "NL_SharedDataContainer.h"

namespace NLE
{
	namespace Core
	{
		class DataDistributor
		{
		public:
			DataDistributor(uint_fast32_t initSize);
			~DataDistributor();

			std::unique_ptr<SharedDataContainer> const& buildEndpoint(ExecutionDesc execDesc, AccessType preferredAccess);
			std::unique_ptr<SharedDataContainer> const& getEndpoint(uint_fast8_t sysId);
			void requestAdd(double data);
			void requestRemove(uint_fast32_t index);
			void distribute();

		private:
			uint_fast32_t _size;
			std::unordered_map<uint_fast8_t, std::unique_ptr<SharedDataContainer>> _dataContainers;
			std::vector<uint_fast8_t> _systemIds;

			tbb::memory_pool<tbb::scalable_allocator<double>> _additionPool;
			tbb::memory_pool<tbb::scalable_allocator<uint_fast32_t>> _removalPool;

			tbb::concurrent_queue<double, tbb::memory_pool_allocator<double>> _additionQueue;
			tbb::concurrent_queue<uint_fast32_t, tbb::memory_pool_allocator<uint_fast32_t>> _removalQueue;
		};
	}
}

//#include "NL_DataDistributor.inl"
//#undef TBB_PREVIEW_MEMORY_POOL

#endif