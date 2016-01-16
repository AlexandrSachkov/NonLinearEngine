#include "NL_ScriptCallbacks.h"
#include "lua.hpp"
#include "NL_Systems.h"
#include "NL_DeviceCore.h"
#include "NL_ThreadLocal.h"

#include "NL_RenderingEngine.h"
#include "NL_GameManager.h"
#include "NL_Console.h"
#include <string>

namespace NLE
{
	namespace SCRIPT
	{
		int Callback::importScene(lua_State* state)
		{
			lua_settop(state, 1);
			if (lua_isstring(state, 1))
			{
				TLS::StringConverter::reference converter = TLS::strConverter.local();
				static_cast<GameManager*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_GAME_MANAGER))
					->importScene(converter.from_bytes(lua_tostring(state, 1)));
				return 0;
			}
			return 0;
		}

		int Callback::printConsole(lua_State* state)
		{
			lua_settop(state, 1);
			if (lua_isstring(state, 1))
			{
				CONSOLE::out(CONSOLE::STANDARD, lua_tostring(state, 1));
				return 0;
			}
			return 0;
		}
	}
}