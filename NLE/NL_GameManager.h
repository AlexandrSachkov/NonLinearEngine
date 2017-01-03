#ifndef NL_GAME_MANAGER_H_
#define NL_GAME_MANAGER_H_

#include "NL_IGameManager.h"
#include "NL_ISerializer.h"
#include "NL_OperationBuffer.h"
#include "NL_IWindowManager.h"
#include "NL_IRenderingEngine.h"
#include "NL_IScriptingEngine.h"
#include "NL_IFileIOManager.h"
#include "NL_EngineServices.h"

#include "lua.hpp"
#include <LuaIntf.h>

#include <functional>

namespace NLE
{	
	namespace GAME
	{
		class Game;
		class Scene;
		class GameObject;
		
		class GameManager : public IGameManager, public std::enable_shared_from_this<GameManager>
		{
		public:
			GameManager(
				EngineServices eServices,
				IWindowManagerSP windowManager,
				IO::IFileIOManagerSP file,
				SERIALIZATION::ISerializerSP serializer,
				GRAPHICS::IRenderingEngineSP renderingEngine,
				SCRIPT::IScriptingEngineSP scriptingEngine);
			~GameManager();

			void update(SystemServices& sServices, double deltaT);
			bool hasUnsavedChanges();
			void newGame();
			void newScene();
			void loadGame(std::wstring path);
			void loadScene(std::wstring path);
			void loadSceneByName(std::wstring name);
			void addScene(std::wstring name, std::wstring path);
			void removeScene(std::wstring name);
			void setInitialScene(std::wstring name);
			
			void saveGame(std::wstring name);
			void saveScene(std::wstring name);
			void quitGame();
			ExecStatus getExecutionStatus();

			Game& getGame();
			Scene& getCurrentScene();

			static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<GameManager>("GameManager")
					.addFunction("getGame", &GameManager::getGame)
					.addFunction("getCurrentScene", &GameManager::getCurrentScene)
					.endClass();
			}

		private:
			void updateGame(Game* game);
			void updateScene(Scene* scene);

			ExecStatus _execStatus;
			EngineServices _eServices;
			IWindowManagerSP _windowManager;
			IO::IFileIOManagerSP _file;
			SERIALIZATION::ISerializerSP _serializer;
			GRAPHICS::IRenderingEngineSP _renderingEngine;
			SCRIPT::IScriptingEngineSP _scriptingEngine;

			OperationBuffer _opBuffer;

			Game* _game;
			Scene* _currentScene;
		};
	}

}


#endif