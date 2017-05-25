#include "NL_GameManager.h"

#include "NL_RenderingEngine.h"
#include "NL_ScriptingEngine.h"
#include "NL_ThreadLocal.h"
#include "NL_GameObject.h"
#include "NL_EngineServices.h"
#include "NL_SharedData.h"
#include "NL_IWindowManager.h"

#include <fstream>

namespace NLE
{
	namespace GAME
	{
		GameManager::GameManager(
			EngineServices eServices,
			IWindowManagerSP windowManager,
			IO::IFileIOManagerSP file,
			SERIALIZATION::ISerializerSP serializer,
			GRAPHICS::IRenderingEngineSP renderingEngine,
			SCRIPT::IScriptingEngineSP scriptingEngine
			) :
			_eServices(eServices),
			_windowManager(windowManager),
			_file(file),
			_serializer(serializer),
			_renderingEngine(renderingEngine),
			_scriptingEngine(scriptingEngine)
		{
			_execStatus = ExecStatus::CONTINUE;
			newGame();


			/*
			_commandBuffer.addFunction(COMMAND::RESTART_GAME,	[&](COMMAND::Data data) { _execStatus = RESTART; });




			_commandBuffer.addFunction(COMMAND::ADD_OBJECT, [&](COMMAND::Data data) {
				_currentScene->addObject(new GameObject());
			});

			_commandBuffer.addFunction(COMMAND::UPDATE_OBJECT, [&](COMMAND::Data data) {
				_currentScene->addObject(data.gameObject);
			});

			_commandBuffer.addFunction(COMMAND::LOAD_OBJECT, [&](COMMAND::Data data) {
				std::wstring path = TLS::strConverter.local().from_bytes(data.name);

				_file->readAsync(path + L".nleobject", [=](std::vector<char>* data) {
					GameObject* object = _serializer.deserialize<GameObject>(data);
					delete data;
					COMMAND::Data updateData;
					updateData.gameObject = object;
					_commandBuffer.queueCommand(COMMAND::UPDATE_OBJECT, updateData);

				}, [=]() {
					eServices.console->push(CONSOLE::ERR, L"Failed to load game object " + path);
				});
			});

			_commandBuffer.addFunction(COMMAND::SAVE_OBJECT, [&](COMMAND::Data data) {
				auto* objectData = _serializer.serialize<GameObject>(data.gameObject);

				_file->writeAsync(data.scene->getName() + L".nleobject", objectData, [=](std::vector<char>* serializedData) {
					delete serializedData;
					eServices.console->push(CONSOLE::STANDARD, L"Successfully saved game object " + data.gameObject->getName());

				}, [=](std::vector<char>* serializedData) {
					delete serializedData;
					eServices.console->push(CONSOLE::ERR, L"Failed to save game object " + data.gameObject->getName());
				});
			});*/

		}

		GameManager::~GameManager()
		{
		}

		void GameManager::update(SystemServices& sServices, double deltaT)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			auto& ex = TLS::scriptExecutor.local();

			ex.executeContextScript(_game->getScriptingContext(), SCRIPT::ON_UPDATE);
			ex.executeContextScript(_currentScene->getScriptingContext(), SCRIPT::ON_UPDATE);

			DATA::SharedData& data = _eServices.data->getData();
			data.sysExecutionTimes.set(GAME_MANAGER, timer.deltaT());
		}

		bool GameManager::hasUnsavedChanges()
		{
			return true;
		}

		void GameManager::newGame()
		{
			/*_game = std::make_unique<Game>(_eServices.console);
			newScene();
			_eServices.console->push(CONSOLE::STANDARD, "Starting new game.");*/
		}

		void GameManager::newScene()
		{
			/*_currentScene = std::make_unique<Scene>();
			_eServices.console->push(CONSOLE::STANDARD, "Starting new scene.");*/
		}

		void GameManager::loadGame(std::string path)
		{
			/*std::vector<char>* data = _file->read(path);
			if (data)
			{
				Game* game = _serializer->deserialize<Game>(data);
				delete data;
				_eServices.console->push(CONSOLE::STANDARD, "Successfully loaded game: " + path);
				updateGame(game);
			}
			else
			{
				_eServices.console->push(CONSOLE::ERR, "Failed to load game: " + path);
			}*/
		}

		void GameManager::loadScene(std::string path)
		{
			/*std::vector<char>* data = _file->read(path);
			if (data)
			{
				Scene* scene = _serializer->deserialize<Scene>(data);
				delete data;
				_eServices.console->push(CONSOLE::STANDARD, "Successfully loaded scene: " + path);
				updateScene(scene);
			}
			else
			{
				_eServices.console->push(CONSOLE::ERR, "Failed to load scene: " + path);
			}*/
		}

		void GameManager::loadSceneByName(std::string name)
		{
			/*auto scenePath = _game->getScenePath(name);
			if (scenePath.compare("") != 0)
			{
				loadScene(scenePath);
			}
			else
			{
				_eServices.console->push(CONSOLE::ERR, "Failed to find scene by name: " + name);
			}*/
		}

		void GameManager::updateGame(Game* game)
		{
				/*game->attachConsole(_eServices.console);
				auto& ex = TLS::scriptExecutor.local();
				ex.executeContextScript(_game->getScriptingContext(), SCRIPT::ON_EXIT);
				_game = std::unique_ptr<Game>(game);

				ex.executeContextScript(_game->getScriptingContext(), SCRIPT::ON_INIT);

				std::string initialSceneName = game->getInitialScene();
				if (initialSceneName.compare("") != 0)
				{
					loadSceneByName(initialSceneName);
				}	*/	
		}

		void GameManager::updateScene(Scene* scene)
		{
				auto& ex = TLS::scriptExecutor.local();
				ex.executeContextScript(_currentScene->getScriptingContext(), SCRIPT::ON_EXIT);
				_currentScene = std::unique_ptr<Scene>(scene);

				ex.executeContextScript(_currentScene->getScriptingContext(), SCRIPT::ON_INIT);
		}
		
		void GameManager::saveGame(std::string name)
		{
			/*if (!name.empty()) {
				_game->setName(name);
			}

			auto* gameData = _serializer->serialize<Game>(_game.get());

			if (_file->write(_game->getName() + ".nlegame", gameData))
			{
				delete gameData;
				_eServices.console->push(CONSOLE::STANDARD, "Successfully saved game: " + _game->getName());
			}
			else
			{
				delete gameData;
				_eServices.console->push(CONSOLE::ERR, "Failed to save game: " + _game->getName());
			}*/
		}

		void GameManager::saveScene(std::string name)
		{
			/*if (!name.empty()) {
				_currentScene->setName(name);
			}

			auto* sceneData = _serializer->serialize<Scene>(_currentScene.get());
			if (_file->write(_currentScene->getName() + ".nlescene", sceneData))
			{
				delete sceneData;
				_eServices.console->push(CONSOLE::STANDARD, "Successfully saved scene: " + _currentScene->getName());
			}
			else
			{
				delete sceneData;
				_eServices.console->push(CONSOLE::ERR, "Failed to save scene: " + _currentScene->getName());
			}*/
		}

		void GameManager::quitGame()
		{
			auto& ex = TLS::scriptExecutor.local();

			ex.executeContextScript(_currentScene->getScriptingContext(), SCRIPT::ON_EXIT);
			ex.executeContextScript(_game->getScriptingContext(), SCRIPT::ON_EXIT);

			_execStatus = TERMINATE;
		}

		ExecStatus GameManager::getExecutionStatus()
		{
			return _execStatus;
		}

		Game& GameManager::getGame()
		{
			return *_game;
		}

		Scene& GameManager::getCurrentScene()
		{
			return *_currentScene;
		}
	}
}