#include "NL_ScriptingEngine.h"
#include "NL_ThreadLocal.h"

namespace NLE
{
	namespace SCRIPT
	{
		ScriptingEngine::ScriptingEngine(EngineServices& eServices) :
			_eServices(eServices)
		{

		}

		ScriptingEngine::~ScriptingEngine()
		{

		}

		bool ScriptingEngine::initialize()
		{
			return true;
		}

		void ScriptingEngine::update(SystemServices* sServices, DataManager* data, double deltaT)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			data->out.scriptingEngineTime = timer.deltaT();
		}
	}
}