#ifndef NL_DATA_MANAGER_H_
#define NL_DATA_MANAGER_H_

#include "NL_SharedData.h"

namespace NLE
{
	class DataManager
	{
	public:
		DataManager();
		~DataManager();

		void update();

		SharedData in;
		SharedData out;
	};
}

#endif
