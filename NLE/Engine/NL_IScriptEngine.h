#ifndef NL_I_SCRIPT_ENGINE_H_
#define NL_I_SCRIPT_ENGINE_H_

#include "NLCore\NL_ISystem.h"

namespace NLE
{
	namespace SCRIPT
	{
		class IScriptEngine : public Core::ISystem
		{
		public:
			virtual void executeScript(const char* script) = 0;
		};
	}
}

#endif