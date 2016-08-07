#ifndef NL_I_SCRIPTING_ENGINE_H_
#define NL_I_SCRIPTING_ENGINE_H_

#include "NL_ISystem.h"

namespace NLE
{
	namespace SCRIPT
	{
		class IScriptingEngine_SysService
		{

		};

		class IScriptingEngine : public ISystem, public IScriptingEngine_SysService
		{
		public:
			virtual bool initialize() = 0;
		};
	}
}

#endif
