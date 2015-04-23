#ifndef NL_SHARED_DATA_CONTAINER_H_
#define NL_SHARED_DATA_CONTAINER_H_

#include <algorithm>
#include <vector>

#ifndef TBB_PREVIEW_MEMORY_POOL
#define TBB_PREVIEW_MEMORY_POOL 1
#endif

#include "tbb\memory_pool.h"
#include "tbb\concurrent_queue.h"

#include "NL_DataPacket.h"

namespace NLE
{
	namespace Core
	{
		enum AccessType { READ_ONLY, READ_WRITE };
		enum ChangeType { ADD, REMOVE, MODIFY };

		class Change
		{
		public:
			Change()
			{
			}

			Change(uint_fast32_t index, double data)
			{
				_index = index;
				_data = data;
			}

			Change(double data)
			{
				_data = data;
			}

			Change(uint_fast32_t index)
			{
				_index = index;
			}

			~Change()
			{
			}

			uint_fast32_t _index;
			double _data;
		};

		class DataDistributor;

		class SharedDataContainer
		{
			friend class DataDistributor;
		public:
			SharedDataContainer(DataDistributor* distributor, AccessType accessType, uint_fast32_t initSize);
			~SharedDataContainer();

			AccessType getAccessType();
			uint_fast32_t getChange(uint_fast32_t index);
			uint_fast32_t getNumChanges();

			void add(double data);
			void remove(uint_fast32_t index);
			void modify(uint_fast32_t index, double data);

			uint_fast32_t size();
			double& get(uint_fast32_t index);

			void applyUpdates();

		private:
			void local_remove(uint_fast32_t index);
			void distributor_add(double data);
			void distributor_remove(uint_fast32_t index);
			void distributor_modify(uint_fast32_t index, double data);

			DataDistributor* _distributor;
			AccessType _accessType;
			std::vector<double, tbb::scalable_allocator<double>> _data;

			tbb::memory_pool<tbb::scalable_allocator<uint_fast32_t>> _changesPool;
			std::vector<uint_fast32_t, tbb::memory_pool_allocator<uint_fast32_t>> _changes;

			tbb::memory_pool<tbb::scalable_allocator<std::pair<uint_fast32_t, double>>> _asyncChangesPool;
			tbb::concurrent_queue<
				std::pair<ChangeType, Change>, 
				tbb::memory_pool_allocator<std::pair<ChangeType, Change>>
			> _asyncChanges;
		};
	}
}

//#include "NL_SharedDataContainer.inl"
//#undef TBB_PREVIEW_MEMORY_POOL

#endif