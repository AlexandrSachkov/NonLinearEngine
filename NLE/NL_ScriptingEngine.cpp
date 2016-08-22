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

			int myNum = _eServices.data->getData().testInt.get();
			_eServices.console->push(CONSOLE::DEBUG, "My Number is: " + std::to_string(myNum));
			_eServices.data->getData().testInt.set(myNum + 1);

			//data->out.scriptingEngineTime = timer.deltaT();
		}
	}
}