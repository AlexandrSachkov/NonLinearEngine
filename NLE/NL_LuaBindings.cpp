#include "NL_LuaBindings.h"
#include "NL_Globals.h"
#include "NL_ConsoleQueue.h"
#include "NL_Game.h"
#include "NL_ScriptingContext.h"

#include "lua.hpp"
#include <LuaIntf.h>

namespace NLE
{
	namespace SCRIPT
	{
		void Bindings::attach(lua_State* state)
		{
			auto module = LuaIntf::LuaBinding(state).beginModule("nle");
			
			CONSOLE::attachBindings(module);
			GAME::Game::attachBindings(module);
			ScriptingContext::attachBindings(module);

			module.endModule();
		}
	}
}