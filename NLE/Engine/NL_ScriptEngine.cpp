#include "NL_ScriptEngine.h"

#include "NLCore\NL_IEngine.h"
#include "NLCore\NL_SDistributor.h"
#include "NL_SharedContainers.h"
#include "NL_Systems.h"
#include "NL_ThreadLocal.h"

#include <assert.h>

namespace NLE
{
	namespace SCRIPT
	{
		ScriptEngine::ScriptEngine() :
			_initialized(false)
		{
			_running.fetch_and_store(false);
		}

		ScriptEngine::~ScriptEngine()
		{
			
		}

		bool ScriptEngine::initialize(Core::IEngine& engine)
		{
			assert(!_initialized);
			_procedure = [&]() {
				std::string script;
				while (_scripts.try_pop(script))
				{
					TLS::ScriptExecutor::reference executor = TLS::scriptExecutor.local();
					executor.executeScript(script.c_str());
				}
			};
			return true;
		}

		void ScriptEngine::release()
		{
			_initialized = false;
		}

		bool ScriptEngine::initialized()
		{
			return _initialized;
		}

		std::function<void()> const& ScriptEngine::getExecutionProcedure()
		{
			return _procedure;
		}

		Core::ISystem& ScriptEngine::getInterface()
		{
			return *this;
		}

		void ScriptEngine::executeScript(const char* script)
		{
			_scripts.push(script);
		}
	}
}