#include "NL_GameManager.h"

#include "NL_RenderingEngine.h"
#include "NL_UiManager.h"
#include "NL_ScriptingEngine.h"
#include "NL_Game.h"
#include "NL_Scene.h"

#include "cereal/archives/json.hpp"
#include "cereal\types\string.hpp"
#include "cereal\types\memory.hpp"

#include <fstream>

namespace NLE
{
	namespace GAME
	{
		GameManager::GameManager(
			EngineServices& eServices,
			IO::FileIOManager& file,
			SERIALIZATION::Serializer& serializer,
			GRAPHICS::RenderingEngine* const renderingEngine,
			UI::UiManager* const uiManager,
			SCRIPT::ScriptingEngine* const scriptingEngine
			) :
			_eServices(eServices),
			_file(file),
			_serializer(serializer),
			_renderingEngine(renderingEngine),
			_uiManager(uiManager),
			_scriptingEngine(scriptingEngine)
		{
			_execStatus = ExecStatus::CONTINUE;

			_game = std::make_unique<Game>();
			_currentScene = std::make_unique<Scene>();
		}

		GameManager::~GameManager()
		{
		}

		void GameManager::update(SystemServices& sServices, DataManager& data, double deltaT)
		{
			processCommands();
		}

		void GameManager::queueCommand(Command& command)
		{
			_commands.push(command);
		}

		void GameManager::processCommands()
		{
			Command command;
			while (_commands.pop(command))
			{
				switch (command.type)
				{
				case QUIT_GAME:
					_execStatus = TERMINATE;
					break;

				case RESTART_GAME:
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

		}

		void GameManager::restartGame()
		{

		}

		void GameManager::updateGame(Game* game)
		{

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