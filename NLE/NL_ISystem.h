#ifndef NL_I_SYSTEM_H_
#define NL_I_SYSTEM_H_

#include "NL_SystemServices.h"
#include "NL_DataManager.h"

namespace NLE
{
	class ISystem
	{
	public:
		virtual void update(SystemServices& sServices, DataManager& data, double deltaT) = 0;
	};
}


#endif