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
			_executionError(L"")
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

		void ScriptExecutor::registerCallback(std::wstring name, int(*callback)(lua_State* state))
		{
			auto& strCnv = TLS::strConverter.local();
			lua_register(_state, strCnv.to_bytes(name).c_str(), callback);
		}

		bool ScriptExecutor::executeContextScript(ScriptingContext& context, std::wstring name)
		{
			if (!context.getScriptStatus(name))
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
				CONSOLE::GLOBAL_CONSOLE_QUEUE->push(CONSOLE::ERR, L"Script '" + name + L"' failed to execute.");
				return false;
			}
		}

		bool ScriptExecutor::executeScript(std::wstring script)
		{
			_executionError = L"";

			if (script.compare(L"") == 0) return true;

			auto& strCnv = TLS::strConverter.local();
			lua_settop(_state, 0);
			if (luaL_loadstring(_state, strCnv.to_bytes(script).c_str()))
			{
				_executionError = TLS::strConverter.local().from_bytes(lua_tostring(_state, -1));
				CONSOLE::GLOBAL_CONSOLE_QUEUE->push(CONSOLE::ERR, _executionError);
				return false;
			}
			if (lua_pcall(_state, 0, LUA_MULTRET, 0))
			{
				_executionError = TLS::strConverter.local().from_bytes(lua_tostring(_state, -1));
				CONSOLE::GLOBAL_CONSOLE_QUEUE->push(CONSOLE::ERR, _executionError);
				return false;
			}
			return true;
		}

		std::wstring ScriptExecutor::getExecutionError()
		{
			return _executionError;
		}

		void ScriptExecutor::applyContext(ScriptingContext& context)
		{
			auto module = LuaIntf::LuaBinding(_state).beginModule("nle");
			context.getParent()->bind(module);
			module.endModule();
		}
	}

}