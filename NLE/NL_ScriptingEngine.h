#ifndef NL_SCRIPTING_ENGINE_H_
#define NL_SCRIPTING_ENGINE_H_

#include "NL_IScriptingEngine.h"

namespace NLE
{
	class EngineServices;
	namespace SCRIPT
	{
		class ScriptingEngine : public IScriptingEngine
		{
		public:
			ScriptingEngine(EngineServices& eServices);
			~ScriptingEngine();

			bool initialize();
			void update(SystemServices* sServices, double deltaT);

		private:
			EngineServices& _eServices;
		};
	}
}

#endif
