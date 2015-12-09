#include "NL_ScriptExecutor.h"
#include "NL_ScriptCallbacks.h"
#include "NL_Console.h"

namespace NLE
{
	namespace SCRIPT
	{
		ScriptExecutor::ScriptExecutor()
		{
			_state = luaL_newstate();
			luaL_openlibs(_state);

			lua_register(_state, "NLE_importScene", Callback::importScene);
			lua_register(_state, "NLE_setScreenDimensions", Callback::setScreenDimensions);
			lua_register(_state, "NLE_setFullscreen", Callback::setFullscreen);
		}

		ScriptExecutor::~ScriptExecutor()
		{
			lua_close(_state);
		}

		lua_State* ScriptExecutor::getState()
		{
			return _state;
		}

		bool ScriptExecutor::executeScript(const char* script)
		{
			lua_settop(_state, 0);
			if (luaL_loadstring(_state, script))
			{
				CONSOLE::out(CONSOLE::ERR, lua_tostring(_state, -1));
				return false;
			}
			if (lua_pcall(_state, 0, LUA_MULTRET, 0))
			{
				CONSOLE::out(CONSOLE::ERR, lua_tostring(_state, -1));
				return false;
			}
			return true;
		}
	}
}