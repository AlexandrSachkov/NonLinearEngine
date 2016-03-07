#ifndef NL_GAME_MANAGER_H_
#define NL_GAME_MANAGER_H_

#include "NL_IGameManager.h"
#include "NL_ISystem.h"
#include "NL_EngineServices.h"
#include "NL_Queue.h"

#include <functional>

namespace NLE
{
	enum ExecStatus
	{
		CONTINUE,
		TERMINATE,
		RESTART
	};

	namespace GRAPHICS
	{
		class RenderingEngine;
	}
	namespace UI
	{
		class UiManager;
	}
	namespace SCRIPT
	{
		class ScriptingEngine;
	}
	namespace GAME
	{
		class Game;
		class Scene;
		class GameManager : public IGameManager, public ISystem
		{
		public:
			GameManager(EngineServices& eServices);
			~GameManager();

			bool initialize(
				GRAPHICS::RenderingEngine* renderingEngine,
				UI::UiManager* uiManager,
				SCRIPT::ScriptingEngine* scriptingEngine);

			void update(SystemServices& sServices, DataManager& data, double deltaT);
			void queueCommand(Command& command);

			ExecStatus getExecutionStatus();

		private:
			void processCommands();
			void loadGame(std::wstring game);
			void saveGame();
			void quitGame();
			void restartGame();
			void loadScene(std::wstring scene);
			void loadGameObject(std::wstring gameObject);
			void unloadGameObject(std::wstring gameObject);
			void importMesh(std::wstring mesh);

			ExecStatus _execStatus;

			EngineServices& _eServices;
			GRAPHICS::RenderingEngine* _renderingEngine;
			UI::UiManager* _uiManager;
			SCRIPT::ScriptingEngine* _scriptingEngine;

			Queue<Command> _commands;

			Game* _game;
			Scene* _currentScene;
		};
	}

}


#endif