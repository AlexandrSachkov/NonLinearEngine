#include "NL_UiManager.h"
#include "NL_Console.h"
#include "NL_ThreadLocal.h"

#include "lua.hpp"

#include <assert.h>
#include <string>

namespace NLE
{
	namespace UI
	{
		UiManager::UiManager() :
			_initialized(false)
		{
		}

		UiManager::~UiManager()
		{
		}

		bool UiManager::initialize(Core::IEngine& engine)
		{
			assert(!_initialized && _printConsole);

			_initialized = true;
			return _initialized;
		}

		void UiManager::release()
		{
			_initialized = false;
		}

		bool UiManager::initialized()
		{
			return _initialized;
		}

		std::function<void()> const& UiManager::getExecutionProcedure()
		{
			_procedure = [&]() {
				CONSOLE::Console::instance().outputConsole();

				TLS::ScriptExecutor::reference executor = TLS::scriptExecutor.local();
				
				std::pair<std::string, int(*)(lua_State* state)> callback;
				while (_callbacks.try_pop(callback))
				{
					executor.registerCallback(callback.first, callback.second);
				}

				std::string script;
				while (_scripts.try_pop(script))
				{				
					executor.executeScript(script.c_str());
				}			
			};

			return _procedure;
		}

		Core::ISystem& UiManager::getInterface()
		{
			return *this;
		}

		void UiManager::bindScriptCallback(const char* name, int(*callback)(lua_State* state), bool async)
		{
			if (async)
			{
				_callbacks.push(std::make_pair<>(name, callback));
			}
			else
			{
				TLS::ScriptExecutor::reference executor = TLS::scriptExecutor.local();
				executor.registerCallback(name, callback);
			}
		}

		void UiManager::executeScript(const char* script, bool async)
		{
			if (async)
			{
				_scripts.push(script);
			}
			else
			{
				TLS::ScriptExecutor::reference executor = TLS::scriptExecutor.local();
				executor.executeScript(script);
			}			
		}
	}
}