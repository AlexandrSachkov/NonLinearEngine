#ifndef NL_RESOURCE_MANAGER_H_
#define NL_RESOURCE_MANAGER_H_

#include "NL_IResourceManager.h"
#include "NL_Game.h"
#include "NL_Scene.h"
#include "NL_GameObject.h"
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

			GAME::Game* createGame();
			GAME::Scene* createScene();
			GAME::GameObject* createGameObject();

			GAME::Game* createGameFromFile(std::wstring path);
			GAME::Scene* createSceneFromFile(std::wstring path);
			GAME::GameObject* createGameObjectFromFile(std::wstring path);

		private:
			EngineServices _eServices;
		};
	}
}

#endif