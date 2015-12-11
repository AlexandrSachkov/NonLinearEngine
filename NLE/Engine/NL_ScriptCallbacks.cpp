#include "NL_ScriptCallbacks.h"
#include "lua.hpp"
#include "NL_Systems.h"
#include "NLCore\NL_DeviceCore.h"
#include "NL_ThreadLocal.h"

#include "NL_RenderingEngine.h"
#include "NL_CameraManager.h"
#include "NL_SceneManager.h"
#include "NL_Console.h"
#include <string>

namespace NLE
{
	namespace SCRIPT
	{
		int Callback::setScreenDimensions(lua_State* state)
		{
			lua_settop(state, 2);
			if (lua_isnumber(state, 1) && lua_isnumber(state, 2))
			{
				auto width = lua_tointeger(state, 1);
				auto height = lua_tointeger(state, 2);

				static_cast<GRAPHICS::RenderingEngine*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERING_ENGINE))
					->setScreenDimensions((uint_fast32_t)width, (uint_fast32_t)height);
				static_cast<GRAPHICS::ICameraManager*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_CAMERA_MANAGER))
					->setScreenDimensions((uint_fast32_t)width, (uint_fast32_t)height);
				return 0;
			}
			return 0;
		}

		int Callback::setFullscreen(lua_State* state)
		{
			lua_settop(state, 1);
			if (lua_isboolean(state, 1))
			{
				static_cast<GRAPHICS::RenderingEngine*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERING_ENGINE))
					->setFullscreen(lua_toboolean(state, 1) == 1);
				return 0;
			}
			return 0;
		}

		int Callback::importScene(lua_State* state)
		{
			lua_settop(state, 1);
			if (lua_isstring(state, 1))
			{
				TLS::StringConverter::reference converter = TLS::strConverter.local();
				static_cast<SceneManager*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_SCENE_MANAGER))
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

		int Callback::getCanvasBgColor(lua_State* state)
		{

			return 0;
		}

		int Callback::setCanvasBgColor(lua_State* state)
		{
			return 0;
		}
	}
}