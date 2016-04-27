#ifndef NL_GAME_MANAGER_H_
#define NL_GAME_MANAGER_H_

#include "NL_IGameManager.h"
#include "NL_ISystem.h"
#include "NL_EngineServices.h"
#include "NL_Queue.h"
#include "NL_FileIOManager.h"
#include "NL_Serializer.h"

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
			GameManager(
				EngineServices& eServices,
				IO::FileIOManager& file,
				SERIALIZATION::Serializer& serializer,
				GRAPHICS::RenderingEngine* const renderingEngine,
				UI::UiManager* const uiManager,
				SCRIPT::ScriptingEngine* const scriptingEngine);
			~GameManager();

			void update(SystemServices& sServices, DataManager& data, double deltaT);
			void queueCommand(Command& command);

			ExecStatus getExecutionStatus();

		private:
			void processCommands();

			void loadGame(std::wstring game);
			void saveGame();
			void quitGame();
			void restartGame();
			void updateGame(Game* game);
			void loadScene(std::wstring scene);
			void loadGameObject(std::wstring gameObject);
			void unloadGameObject(std::wstring gameObject);
			void importMesh(std::wstring mesh);

			ExecStatus _execStatus;

			EngineServices& _eServices;
			IO::FileIOManager& _file;
			SERIALIZATION::Serializer& _serializer;
			GRAPHICS::RenderingEngine* const _renderingEngine;
			UI::UiManager* const _uiManager;
			SCRIPT::ScriptingEngine* const _scriptingEngine;

			Queue<Command> _commands;

			std::unique_ptr<Game> _game;
			std::unique_ptr<Scene> _currentScene;
		};
	}

}


#endif