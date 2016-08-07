#ifndef NL_LUA_BINDINGS_H_
#define NL_LUA_BINDINGS_H_

struct lua_State;
namespace NLE
{
	namespace SCRIPT
	{
		class Bindings
		{
		public:
			static void attach(lua_State* state);
		};		
	}
}

#endif