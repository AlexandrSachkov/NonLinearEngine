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
			GRAPHICS::RenderingEngine* const renderingEngine,
			UI::UiManager* const uiManager,
			SCRIPT::ScriptingEngine* const scriptingEngine
			) :
			_eServices(eServices),
			_file(file),
			_renderingEngine(renderingEngine),
			_uiManager(uiManager),
			_scriptingEngine(scriptingEngine)
		{
			_execStatus = ExecStatus::CONTINUE;

			_game = std::make_unique<Game>();

			std::stringstream stream;
			{
				cereal::JSONOutputArchive archive(stream);
				archive(CEREAL_NVP(_game));
			}		
			const std::string str = stream.str();
			std::vector<char>* data = new std::vector<char>(str.begin(), str.end());
			_file.writeAsync(L"TestGame.nlegame", data, []() {
				printf("File write succeeded\n");
			}, []() {});

			/*std::unique_ptr<Game> game = nullptr;
			std::ifstream is("TestGame.nlegame");
			cereal::JSONInputArchive ar(is);
			ar(cereal::make_nvp("_game", game));*/

			_currentScene = new Scene();
		}

		GameManager::~GameManager()
		{
			delete _currentScene;	
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