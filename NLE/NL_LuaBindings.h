#pragma once

struct lua_State;
namespace NLE
{
	namespace SCRIPT
	{
		class Bindings
		{
		public:
			static void attach(lua_State* state);
			static void attachMaster(lua_State* state);
		};		
	}
}