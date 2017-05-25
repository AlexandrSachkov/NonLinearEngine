#pragma once

#include "NL_IResourceManager.h"
#include "NL_EngineServices.h"

#include <string>
#include "NL_LuaCustomTypes.h"
#include "LuaIntf.h"

namespace NLE
{
	namespace RESOURCE
	{
		class ResourceManager : public IResourceManager
		{
		public:
			ResourceManager(EngineServices eServices);
			~ResourceManager();

			GAME::Game* createGame(const GAME::GameDesc&);
			GAME::Scene* createScene(const GAME::SceneDesc&);
			GAME::GameObject* createGameObject();

			std::tuple<bool, GAME::GameDesc> loadGameDesc(std::string path);
			bool saveGameDesc(std::string path, const GAME::GameDesc&);
			std::tuple<bool, GAME::SceneDesc> loadSceneDesc(std::string path);
			bool saveSceneDesc(std::string path, const GAME::SceneDesc&);
			GAME::GameObject* createGameObjectFromFile(std::string path);

		private:
			EngineServices _eServices;
		};
	}
}