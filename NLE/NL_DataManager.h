#ifndef NL_DATA_MANAGER_H_
#define NL_DATA_MANAGER_H_

#include "NL_IDataManager.h"
#include "NL_SharedData.h"
#include "tbb/concurrent_vector.h"

namespace NLE
{
	namespace DATA
	{
		class DataManager : public IDataManager
		{
		public:
			DataManager();
			~DataManager();

			void syncData(unsigned int numThreads);
			void requestSync(ISharedEntity* entity);
			SharedData& getData();

		private:
			SharedData _data;
			tbb::concurrent_vector<ISharedEntity*> _entitiesToSync;
		};
	}
}

#endif
