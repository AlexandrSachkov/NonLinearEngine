#ifndef NL_I_SYSTEM_H_
#define NL_I_SYSTEM_H_

#include "NL_DataManager.h"

namespace NLE
{
	class SystemServices;
	class DataManager;
	class ISystem
	{
	public:
		virtual void update(SystemServices* sServices, DataManager* data, double deltaT) = 0;
	};
}


#endif