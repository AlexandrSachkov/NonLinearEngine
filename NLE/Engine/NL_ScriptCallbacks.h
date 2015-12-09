#ifndef NL_LUA_CALLBACKS_H_
#define NL_LUA_CALLBACKS_H_

struct lua_State;
namespace NLE
{
	namespace SCRIPT
	{
		class Callback
		{
		public:
			static int setScreenDimensions(lua_State* state);
			static int setFullscreen(lua_State* state);

			static int importScene(lua_State* state);
		};		
	}
}

#endif