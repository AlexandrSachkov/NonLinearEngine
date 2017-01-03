#include "NL_LuaBindings.h"
#include "NL_Globals.h"
#include "NL_ConsoleQueue.h"
#include "NL_Game.h"
#include "NL_Scene.h"
#include "NL_GameManager.h"
#include "NL_ScriptingContext.h"
#include "NL_GameObject.h"

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
			GAME::GameManager::attachBindings(module);
			GAME::Game::attachBindings(module);
			GAME::Scene::attachBindings(module);
			GAME::GameObject::attachBindings(module);
			ScriptingContext::attachBindings(module);			

			module.endModule();
		}
		void Bindings::attachMaster(lua_State* state)
		{
			auto module = LuaIntf::LuaBinding(state).beginModule("nle");			
			GAME::GameManager::attachMasterBindings(module);
			GAME::Game::attachMasterBindings(module);
			module.endModule();
		}
	}
}