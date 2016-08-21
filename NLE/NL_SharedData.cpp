#include "NL_SharedData.h"
#include "NL_IDataManager.h"

namespace NLE
{
	namespace DATA
	{
		SharedData::SharedData(IDataManager_Data& dataManager) :
			testInt(dataManager, 5)
		{
		}

		SharedData::~SharedData()
		{
		}
	}
}