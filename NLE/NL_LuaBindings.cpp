#include "NL_LuaBindings.h"

#include "lua.hpp"
#include <LuaIntf.h>

namespace NLE
{
	namespace SCRIPT
	{
		void Bindings::attach(lua_State* state)
		{
			LuaIntf::LuaBinding(state).beginModule("nle")
					.beginModule("script")
						.addConstant("test", 5)
					.endModule()
				.endModule();
		}
	}
}