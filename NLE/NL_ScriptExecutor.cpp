#include "NL_ScriptExecutor.h"
#include "NL_ScriptCallbacks.h"

namespace NLE
{
	namespace SCRIPT
	{
		ScriptExecutor::ScriptExecutor()
		{
			_state = luaL_newstate();
			luaL_openlibs(_state);

			//lua_register(_state, "NLE_importScene", Callback::importScene);
			lua_register(_state, "NLE_cout", Callback::printConsole);
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

		bool ScriptExecutor::executeScript(const char* script)
		{
			lua_settop(_state, 0);
			if (luaL_loadstring(_state, script))
			{
				//CONSOLE::out(CONSOLE::ERR, lua_tostring(_state, -1));
				return false;
			}
			if (lua_pcall(_state, 0, LUA_MULTRET, 0))
			{
				//CONSOLE::out(CONSOLE::ERR, lua_tostring(_state, -1));
				return false;
			}
			return true;
		}
	}
}