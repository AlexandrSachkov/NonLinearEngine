#include "NL_GameManager.h"

#include "NL_IRenderingEngine.h"
#include "NL_ThreadLocal.h"
#include "NL_RenderingEngine.h"
#include "NL_UiManager.h"
#include "NL_ScriptingEngine.h"
#include "NL_Game.h"
#include "NL_Scene.h"

#include <assert.h>

namespace NLE
{
	namespace GAME
	{
		GameManager::GameManager(EngineServices& eServices) :
			_eServices(eServices)
		{
			_execStatus = ExecStatus::CONTINUE;
			_renderingEngine = nullptr;
			_uiManager = nullptr;
			_scriptingEngine = nullptr;

			_game = new Game();
			_currentScene = new Scene();
		}

		GameManager::~GameManager()
		{
		}

		bool GameManager::initialize(
			GRAPHICS::RenderingEngine* const renderingEngine,
			UI::UiManager* const uiManager,
			SCRIPT::ScriptingEngine* const scriptingEngine)
		{
			_renderingEngine = renderingEngine;
			_uiManager = uiManager;
			_scriptingEngine = scriptingEngine;

			return true;
		}

		void GameManager::update(SystemServices& sServices, DataManager& data, double deltaT)
		{
			processEvents();
		}

		void GameManager::processEvents()
		{
			Event event;
			while (_events.pop(event))
			{
				switch (event.type)
				{
				case EventType::QUIT_GAME:
					_execStatus = TERMINATE;
					break;

				case EventType::RESTART_GAME:
					_execStatus = RESTART;
					break;

				default:
					break;
				}
			}
		}

		ExecStatus GameManager::getExecutionStatus()
		{
			return _execStatus;
		}

		void GameManager::loadGame(std::wstring game)
		{

		}

		void GameManager::saveGame()
		{

		}

		void GameManager::quitGame()
		{
			_events.push(Event(EventType::QUIT_GAME));
		}

		void GameManager::restartGame()
		{
			_events.push(Event(EventType::RESTART_GAME));
		}

		void GameManager::loadScene(std::wstring scene)
		{

		}

		void GameManager::loadGameObject(std::wstring gameObject)
		{

		}

		void GameManager::unloadGameObject(std::wstring gameObject)
		{

		}

		void GameManager::importMesh(std::wstring mesh)
		{

		}
	}
}