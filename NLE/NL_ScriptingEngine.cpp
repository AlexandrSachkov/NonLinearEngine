#include "NL_ScriptingEngine.h"
#include "NL_ThreadLocal.h"
#include "NL_EngineServices.h"
#include "NL_SharedData.h"

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

		void ScriptingEngine::update(SystemServices* sServices, double deltaT)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			DATA::SharedData& data = _eServices.data->getData();
			data.sysExecutionTimes.set(SCRIPTING_ENGINE, timer.deltaT());
		}
	}
}