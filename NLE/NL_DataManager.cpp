#include "NL_DataManager.h"
#include "NL_ISharedEntity.h"
#include "NL_ThreadLocal.h"

#include "tbb/tbb.h"

namespace NLE
{
	namespace DATA
	{
		DataManager::DataManager() :
			_data(*this)
		{

		}

		DataManager::~DataManager()
		{
		}

		void DataManager::syncData(unsigned int numThreads)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			size_t numEntities = _entitiesToSync.size();
			unsigned int grainSize = (unsigned int)std::ceil((double)numEntities / (double)numThreads);
			tbb::parallel_for(
				tbb::blocked_range<size_t>(0, _entitiesToSync.size(), grainSize == 0 ? 1 : grainSize),
				[&](const tbb::blocked_range<size_t>& r)
			{
				for (uint_fast32_t i = (uint_fast32_t)r.begin(); i < r.end(); ++i)
				{
					_entitiesToSync[i]->sync();
				}
			});
			_entitiesToSync.clear();

			_data.sysExecutionTimes.set(DATA_MANAGER, timer.deltaT());
			_data.sysExecutionTimes.set(DATA_MANAGER, timer.deltaT());
		}

		void DataManager::requestSync(ISharedEntity* entity)
		{
			_entitiesToSync.push_back(entity);
		}

		SharedData& DataManager::getData()
		{
			return _data;
		}
	}
}