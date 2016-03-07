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
		enum EventType
		{
			QUIT_GAME,
			RESTART_GAME
		};

		union EventData
		{
		};

		struct Event
		{
			Event() {}
			Event(EventType type) : type(type) {}
			Event(EventType type, EventData data) : type(type), data(data) {}
			EventType type;
			EventData data;
		};

		class Game;
		class Scene;
		class GameManager : public IGameManager, public ISystem
		{
		public:
			GameManager(EngineServices& eServices);
			~GameManager();

			bool initialize(
				GRAPHICS::RenderingEngine* const renderingEngine,
				UI::UiManager* const uiManager,
				SCRIPT::ScriptingEngine* const scriptingEngine);

			void update(SystemServices& sServices, DataManager& data, double deltaT);

			void loadGame(std::wstring game);
			void saveGame();
			void quitGame();
			void restartGame();

			void loadScene(std::wstring scene);

			void loadGameObject(std::wstring gameObject);
			void unloadGameObject(std::wstring gameObject);

			void importMesh(std::wstring mesh);

			ExecStatus getExecutionStatus();

		private:
			void processEvents();

			ExecStatus _execStatus;

			EngineServices& _eServices;
			GRAPHICS::RenderingEngine* _renderingEngine;
			UI::UiManager* _uiManager;
			SCRIPT::ScriptingEngine* _scriptingEngine;

			Queue<Event> _events;

			Game* _game;
			Scene* _currentScene;
		};
	}

}


#endif