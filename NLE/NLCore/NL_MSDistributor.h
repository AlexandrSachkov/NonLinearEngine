#ifndef NL_MS_DISTRIBUTOR_H_
#define NL_MS_DISTRIBUTOR_H_

#ifndef TBB_PREVIEW_MEMORY_POOL
#define TBB_PREVIEW_MEMORY_POOL 1
#endif

#include "tbb\memory_pool.h"
#include "tbb\scalable_allocator.h"
#include "tbb\concurrent_queue.h"

#include "NL_MasterContainer.h"
#include "NL_SlaveContainer.h"
#include "NL_DataRequest.h"

#include <cstdint>
#include <unordered_map>
#include <memory>

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			class MSDistributor
			{
			public:
				MSDistributor(uint_fast32_t initialSize);
				~MSDistributor();

				MasterContainer& buildMasterEndpoint(uint_fast8_t sysId);
				SlaveContainer& buildSlaveEndpoint(uint_fast8_t sysId);
				void distributeFrom(uint_fast8_t sysId);
				void distributeTo(uint_fast8_t sysId);
				void queueRequest(MasterRequest request);
				void processRequests();

			private:
				void localRemove(uint_fast32_t index);

				std::vector<double, tbb::scalable_allocator<double>> _data;

				std::pair<uint_fast8_t, MasterContainer*> _masterHash;
				std::unordered_map<uint_fast8_t, SlaveContainer*> _slaves;

				tbb::memory_pool<tbb::scalable_allocator<MasterRequest>> _requestPool;
				tbb::concurrent_queue<MasterRequest, tbb::memory_pool_allocator<MasterRequest>> _requestQueue;
			};
		}
	}
}

#endif