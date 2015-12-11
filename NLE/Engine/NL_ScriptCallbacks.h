#ifndef NL_LUA_CALLBACKS_H_
#define NL_LUA_CALLBACKS_H_

#include "tbb\concurrent_unordered_map.h"

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

			static int printConsole(lua_State* state);

			static int getCanvasBgColor(lua_State* state);
			static int setCanvasBgColor(lua_State* state);
		};		
	}
}

#endif