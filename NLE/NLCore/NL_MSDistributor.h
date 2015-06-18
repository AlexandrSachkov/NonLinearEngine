#ifndef NL_MS_DISTRIBUTOR_H_
#define NL_MS_DISTRIBUTOR_H_

#ifndef TBB_PREVIEW_MEMORY_POOL
#define TBB_PREVIEW_MEMORY_POOL 1
#endif

#include "tbb\memory_pool.h"
#include "tbb\scalable_allocator.h"
#include "tbb\concurrent_queue.h"

#include "NL_Distributor.h"
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
			template<typename T>
			class MSDistributor : public Distributor
			{
			public:
				MSDistributor(uint_fast32_t initialSize);
				~MSDistributor();

				MasterContainer<T>& buildMasterEndpoint(uint_fast8_t sysId);
				SlaveContainer<T>& buildSlaveEndpoint(uint_fast8_t sysId);
				void distributeFrom(uint_fast8_t sysId);
				void distributeTo(uint_fast8_t sysId);
				void queueRequest(MasterRequest<T> request);
				void processRequests();
				std::vector<uint_fast8_t>& getEndpoints();

			private:
				void localRemove(uint_fast32_t index);

				std::vector<T, tbb::scalable_allocator<T>> _data;

				std::pair<uint_fast8_t, MasterContainer<T>*> _masterHash;
				std::unordered_map<uint_fast8_t, SlaveContainer<T>*> _slaves;

				tbb::memory_pool<tbb::scalable_allocator<MasterRequest<T>>> _requestPool;
				tbb::concurrent_queue<MasterRequest<T>, tbb::memory_pool_allocator<MasterRequest<T>>> _requestQueue;
				std::vector<uint_fast8_t> _endpoints;
			};
		}
	}
}

#include "NL_MSDistributor.inl"

#endif