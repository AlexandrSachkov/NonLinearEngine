#ifndef NL_I_RESOURCE_MANAGER_H_
#define NL_I_RESOURCE_MANAGER_H_

#include "NL_LuaCustomTypes.h"
#include <LuaIntf.h>
#include <string>


namespace NLE
{
	namespace GAME
	{
		class Game;
		class Scene;
		class GameObject;
	}
	namespace RESOURCE
	{
		class IResourceManager
		{
		public:
			virtual GAME::Game* createGame() = 0;
			virtual GAME::Scene* createScene() = 0;
			virtual GAME::GameObject* createGameObject() = 0;

			virtual GAME::Game* createGameFromFile(std::wstring path) = 0;
			virtual GAME::Scene* createSceneFromFile(std::wstring path) = 0;
			virtual GAME::GameObject* createGameObjectFromFile(std::wstring path) = 0;

			static void attachMasterBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<IResourceManager>("ResourceManager")
					.addFunction("createGame", &IResourceManager::createGame)
					.addFunction("createScene", &IResourceManager::createScene)
					.addFunction("createGameObject", &IResourceManager::createGameObject)
					.addFunction("createGameFromFile", &IResourceManager::createGameFromFile)
					.addFunction("createSceneFromFile", &IResourceManager::createSceneFromFile)
					.addFunction("createGameObjectFromFile", &IResourceManager::createGameObjectFromFile)
					.endClass();
			}
		};
	}
}

#endif