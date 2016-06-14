#ifndef NL_SCRIPTING_COMPONENT_H_
#define NL_SCRIPTING_COMPONENT_H_

#include "NL_ScriptingContext.h"

namespace NLE
{
	namespace GAME
	{
		class ScriptingComponent
		{
		public:
			ScriptingComponent();
			~ScriptingComponent();

			SCRIPT::ScriptingContext& getScriptingContext();

		private:
			SCRIPT::ScriptingContext _scriptingContext;
		};
	}
}

#endif
