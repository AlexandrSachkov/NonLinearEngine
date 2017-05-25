#include "NL_ScriptExecutor.h"
#include "NL_ScriptingContext.h"
#include "NL_ThreadLocal.h"
#include "NL_LuaBindings.h"
#include "NL_Globals.h"
#include "NL_ConsoleQueue.h"
#include "NL_IScriptable.h"

namespace NLE
{
	namespace SCRIPT
	{
		ScriptExecutor::ScriptExecutor() :
			_executionError("")
		{
			_state = luaL_newstate();
			luaL_openlibs(_state);

			Bindings::attach(_state);
		}

		ScriptExecutor::~ScriptExecutor()
		{
			lua_close(_state);
		}

		lua_State* ScriptExecutor::getState()
		{
			return _state;
		}

		void ScriptExecutor::registerCallback(std::string name, int(*callback)(lua_State* state))
		{
			lua_register(_state, name.c_str(), callback);
		}

		bool ScriptExecutor::executeContextScript(ScriptingContext& context, std::string name)
		{
			/*if (!context.getScriptStatus(name))
			{
				return false;
			}

			applyContext(context);
			if (executeScript(context.getScript(name)))
			{
				return true;
			}
			else
			{
				context.flagScript(name, _executionError);
				CONSOLE::GLOBAL_CONSOLE_QUEUE->push(CONSOLE::ERR, "Script '" + name + "' failed to execute.");
				return false;
			}*/
			return false;
		}

		bool ScriptExecutor::executeScript(std::string script)
		{
			_executionError = "";

			if (script.compare("") == 0) return true;

			lua_settop(_state, 0);
			if (luaL_loadstring(_state, script.c_str()))
			{
				_executionError = lua_tostring(_state, -1);
				CONSOLE::GLOBAL_CONSOLE_QUEUE->push(CONSOLE::ERR, _executionError);
				return false;
			}
			if (lua_pcall(_state, 0, LUA_MULTRET, 0))
			{
				_executionError = lua_tostring(_state, -1);
				CONSOLE::GLOBAL_CONSOLE_QUEUE->push(CONSOLE::ERR, _executionError);
				return false;
			}
			return true;
		}

		std::string ScriptExecutor::getExecutionError()
		{
			return _executionError;
		}

		void ScriptExecutor::applyContext(ScriptingContext& context)
		{
			/*auto module = LuaIntf::LuaBinding(_state).beginModule("nle");
			if(context.getParent())
				context.getParent()->bind(module);
			module.endModule();*/
		}
	}

}