#ifndef NL_I_UI_MANAGER_H_
#define NL_I_UI_MANAGER_H_

#include "NL_ISystem.h"

namespace NLE
{
	namespace UI
	{
		class IUiManager_SysService
		{

		};

		class IUiManager : public ISystem, public IUiManager_SysService
		{
		public:
			virtual bool initialize() = 0;
		};
	}
}

#endif
