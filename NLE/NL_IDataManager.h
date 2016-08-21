#ifndef NL_I_DATA_MANAGER_H_
#define NL_I_DATA_MANAGER_H_

namespace NLE
{
	namespace DATA
	{
		class ISharedEntity;
		class SharedData;
		class IDataManager_EService
		{
		public:
			virtual SharedData& getData() = 0;
		};

		class IDataManager_Data
		{
		public:
			virtual void requestSync(ISharedEntity* entity) = 0;
		};

		class IDataManager : public IDataManager_EService, public IDataManager_Data
		{
		public:
			virtual void syncData(unsigned int numThreads) = 0;
		};
	}
}


#endif