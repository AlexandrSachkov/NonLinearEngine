#ifndef NL_SCRIPTING_ENGINE_H_
#define NL_SCRIPTING_ENGINE_H_

#include "NL_IScriptingEngine.h"
#include "NL_EngineServices.h"

namespace NLE
{
	namespace SCRIPT
	{
		class ScriptingEngine : public IScriptingEngine
		{
		public:
			ScriptingEngine(EngineServices& eServices);
			~ScriptingEngine();

			bool initialize();
			void update(SystemServices* sServices, DataManager* data, double deltaT);

		private:
			EngineServices& _eServices;
		};
	}
}

#endif
