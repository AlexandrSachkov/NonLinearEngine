#pragma once

#include "NL_Game.h"
#include "NL_Scene.h"

#include "NL_LuaCustomTypes.h"
#include <LuaIntf.h>
#include <string>


namespace NLE
{
	namespace GAME
	{
		class Scene;
		class GameObject;
	}
	namespace RESOURCE
	{
		class IResourceManager
		{
		public:
			virtual GAME::Game* createGame(const GAME::GameDesc&) = 0;
			virtual GAME::Scene* createScene(const GAME::SceneDesc&) = 0;
			virtual GAME::GameObject* createGameObject() = 0;

			virtual std::tuple<bool, GAME::GameDesc> loadGameDesc(std::string path) = 0;
			virtual bool saveGameDesc(std::string path, const GAME::GameDesc&) = 0;
			virtual std::tuple<bool, GAME::SceneDesc> loadSceneDesc(std::string path) = 0;
			virtual bool saveSceneDesc(std::string path, const GAME::SceneDesc&) = 0;

			virtual GAME::GameObject* createGameObjectFromFile(std::string path) = 0;

			static void attachMasterBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<IResourceManager>("ResourceManager")
					.addFunction("createGame", &IResourceManager::createGame)
					.addFunction("createScene", &IResourceManager::createScene)
					.addFunction("createGameObject", &IResourceManager::createGameObject)
					.addFunction("loadGameDesc", &IResourceManager::loadGameDesc)
					.addFunction("saveGameDesc", &IResourceManager::saveGameDesc)
					.addFunction("loadSceneDesc", &IResourceManager::loadSceneDesc)
					.addFunction("saveSceneDesc", &IResourceManager::saveSceneDesc)
					.addFunction("createGameObjectFromFile", &IResourceManager::createGameObjectFromFile)
					.endClass();
			}
		};
	}
}