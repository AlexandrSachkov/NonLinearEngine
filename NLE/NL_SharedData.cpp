#include "NL_SharedData.h"
#include "NL_IDataManager.h"

namespace NLE
{
	namespace DATA
	{
		SharedData::SharedData(IDataManager_Data& dataManager) :
			sysExecutionTimes(dataManager, NUM_SYSTEMS, 0)
		{
		}

		SharedData::~SharedData()
		{
		}
	}
}