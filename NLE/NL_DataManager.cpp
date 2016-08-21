#include "NL_DataManager.h"
#include "NL_ISharedEntity.h"
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
			unsigned int grainSize = (unsigned int)std::ceil((double)_entitiesToSync.size() / (double)numThreads);
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