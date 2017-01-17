#pragma once

#include "NL_ISystem.h"
#include <memory>

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
			
		};

		typedef std::shared_ptr<IScriptingEngine> IScriptingEngineSP;
		typedef std::shared_ptr<IScriptingEngine_SysService> IScriptingEngine_SysServiceSP;
	}
}
