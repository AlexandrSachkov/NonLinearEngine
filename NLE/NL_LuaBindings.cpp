#include "NL_LuaBindings.h"
#include "NL_Globals.h"
#include "NL_ConsoleQueue.h"
#include "NL_Game.h"
#include "NL_Scene.h"
#include "NL_GameManager.h"
#include "NL_ScriptingContext.h"
#include "NL_GameObject.h"
#include "NL_CommonTypes.h"
#include "NL_IWindowManager.h"
#include "NL_FileIOManager.h"
#include "NL_ResourceManager.h"

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
			Size2D::attachBindings(module);
			Position2D::attachBindings(module);
			Offset2D::attachBindings(module);

			module.endModule();
		}
		void Bindings::attachMaster(lua_State* state)
		{
			auto module = LuaIntf::LuaBinding(state).beginModule("nle");			
			GAME::GameManager::attachMasterBindings(module);
			GAME::GameDesc::attachMasterBindings(module);
			GAME::Game::attachMasterBindings(module);
			GAME::SceneDesc::attachMasterBindings(module);
			GAME::Scene::attachMasterBindings(module);
			GAME::GameObject::attachMasterBindings(module);
			SCRIPT::ScriptingContextDesc::attachMasterBindings(module);
			IWindowManager::attachMasterBindings(module);
			IO::IFileIOManager::attachMasterBindings(module);
			RESOURCE::IResourceManager::attachMasterBindings(module);
			module.endModule();
		}
	}
}