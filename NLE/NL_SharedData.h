#ifndef NL_SHARED_DATA_H_
#define NL_SHARED_DATA_H_

#include "NL_SharedEntry.h"

namespace NLE
{
	namespace DATA
	{
		class IDataManager_Data;
		class SharedData
		{
		public:
			SharedData(IDataManager_Data& dataManager);
			~SharedData();

			SharedEntry<int> testInt;
		};
	}
}

#endif