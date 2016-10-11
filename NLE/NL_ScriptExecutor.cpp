#include "NL_ScriptExecutor.h"
#include "NL_ScriptingContext.h"
#include "NL_ThreadLocal.h"
#include "NL_LuaBindings.h"
#include "NL_Globals.h"
#include "NL_ConsoleQueue.h"

namespace NLE
{
	namespace SCRIPT
	{
		ScriptExecutor::ScriptExecutor() :
			_context(nullptr)
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

		void ScriptExecutor::bindContext(ScriptingContext* context)
		{
			_context = context;
		}

		ScriptingContext* ScriptExecutor::getContext()
		{
			return _context;
		}

		bool ScriptExecutor::executeContextScript(std::wstring name)
		{
			if (!_context)
				return false;

			if (!_context->getScriptStatus(name))
			{
				return false;
			}

			if (executeScript(_context->getScript(name)))
			{
				return true;
			}
			else
			{
				_context->flagScript(name);
				return false;
			}
		}

		bool ScriptExecutor::executeScript(std::wstring script)
		{
			if (script.compare(L"") == 0) return true;

			auto& strCnv = TLS::strConverter.local();
			lua_settop(_state, 0);
			if (luaL_loadstring(_state, strCnv.to_bytes(script).c_str()))
			{
				CONSOLE::GLOBAL_CONSOLE_QUEUE->push(CONSOLE::ERR, lua_tostring(_state, -1));
				return false;
			}
			if (lua_pcall(_state, 0, LUA_MULTRET, 0))
			{
				CONSOLE::GLOBAL_CONSOLE_QUEUE->push(CONSOLE::ERR, lua_tostring(_state, -1));
				return false;
			}
			return true;
		}
	}
}