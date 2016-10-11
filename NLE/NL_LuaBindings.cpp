#include "NL_LuaBindings.h"
#include "NL_Globals.h"
#include "NL_ConsoleQueue.h"

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
			module.endModule();
		}
	}
}