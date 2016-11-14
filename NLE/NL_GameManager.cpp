#include "NL_GameManager.h"

#include "NL_RenderingEngine.h"
#include "NL_ScriptingEngine.h"
#include "NL_Game.h"
#include "NL_Scene.h"
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
			EngineServices& eServices,
			IWindowManager& windowManager,
			IO::IFileIOManager* file,
			SERIALIZATION::ISerializer& serializer,
			GRAPHICS::IRenderingEngine* const renderingEngine,
			SCRIPT::IScriptingEngine* const scriptingEngine
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

		void GameManager::update(SystemServices* sServices, double deltaT)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			_opBuffer.replayOperations();

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
			_opBuffer.queueOperation([&]() {
				_game = new Game(this, _eServices.console);
				_currentScene = new Scene(this);
				_eServices.console->push(CONSOLE::STANDARD, L"Starting new game.");
			});
		}

		void GameManager::loadGame(std::wstring path)
		{
			_opBuffer.queueOperation([&, path]() {
				_file->readAsync(path, [=](std::vector<char>* data) {
					Game* game = _serializer.deserialize<Game>(data);
					delete data;
					_eServices.console->push(CONSOLE::STANDARD, L"Successfully loaded game: " + path);
					updateGame(game);
				}, [=]() {
					_eServices.console->push(CONSOLE::ERR, L"Failed to load game: " + path);
				});
			});
		}

		void GameManager::loadScene(std::wstring path)
		{
			_opBuffer.queueOperation([&, path]() {
				_file->readAsync(path, [=](std::vector<char>* data) {
					Scene* scene = _serializer.deserialize<Scene>(data);
					delete data;
					_eServices.console->push(CONSOLE::STANDARD, L"Successfully loaded scene: " + path);
					updateScene(scene);
				}, [=]() {
					_eServices.console->push(CONSOLE::ERR, L"Failed to load scene: " + path);
				});
			});
		}

		void GameManager::loadSceneByName(std::wstring name)
		{
			_opBuffer.queueOperation([&, name]() {
				std::wstring scenePath;
				if (_game->getScenePath(name, scenePath))
				{
					loadScene(scenePath);
				}
				else
				{
					_eServices.console->push(CONSOLE::ERR, L"Failed to find scene by name: " + name);
				}	
			});
		}

		void GameManager::updateGame(Game* game)
		{
			_opBuffer.queueOperation([&, game]() {
				game->setGameManager(*this);
				game->attachConsole(_eServices.console);
				auto& ex = TLS::scriptExecutor.local();
				ex.executeContextScript(_game->getScriptingContext(), SCRIPT::ON_EXIT);
				delete _game;
				_game = game;

				ex.executeContextScript(_game->getScriptingContext(), SCRIPT::ON_INIT);
			});
		}

		void GameManager::updateScene(Scene* scene)
		{
			_opBuffer.queueOperation([&, scene]() {
				scene->setGameManager(*this);
				auto& ex = TLS::scriptExecutor.local();
				ex.executeContextScript(_currentScene->getScriptingContext(), SCRIPT::ON_EXIT);
				delete _currentScene;
				_currentScene = scene;

				ex.executeContextScript(_currentScene->getScriptingContext(), SCRIPT::ON_INIT);
			});
		}

		void GameManager::saveGame(std::wstring name)
		{
			_opBuffer.queueOperation([&, name]() {
				if (!name.empty()) {
					_game->setName(name);
				}

				auto* gameData = _serializer.serialize<Game>(_game);
				_file->writeAsync(_game->getName() + L".nlegame", gameData, [=](std::vector<char>* serializedData) {
					delete serializedData;
					_eServices.console->push(CONSOLE::STANDARD, L"Successfully saved game: " + _game->getName());

				}, [=](std::vector<char>* serializedData) {
					delete serializedData;
					_eServices.console->push(CONSOLE::ERR, L"Failed to save game: " + _game->getName());
				});
			});
		}

		void GameManager::saveScene(std::wstring name)
		{
			_opBuffer.queueOperation([&, name]() {
				if (!name.empty()) {
					_currentScene->setName(name);
				}

				auto* sceneData = _serializer.serialize<Scene>(_currentScene);
				_file->writeAsync(_currentScene->getName() + L".nlescene", sceneData, [=](std::vector<char>* serializedData) {
					delete serializedData;
					_eServices.console->push(CONSOLE::STANDARD, L"Successfully saved scene: " + _currentScene->getName());

				}, [=](std::vector<char>* serializedData) {
					delete serializedData;
					_eServices.console->push(CONSOLE::ERR, L"Failed to save scene: " + _currentScene->getName());
				});
			});
		}

		void GameManager::quitGame()
		{
			_opBuffer.queueOperation([&]() {
				auto& ex = TLS::scriptExecutor.local();

				ex.executeContextScript(_currentScene->getScriptingContext(), SCRIPT::ON_EXIT);
				ex.executeContextScript(_game->getScriptingContext(), SCRIPT::ON_EXIT);

				_execStatus = TERMINATE;
			});
		}

		void GameManager::addScene(std::wstring name, std::wstring path)
		{
			_opBuffer.queueOperation([&, name, path]() {
				_game->addScene(name, path);
			});
		}

		void GameManager::removeScene(std::wstring name)
		{
			_opBuffer.queueOperation([&, name]() {
				_game->removeScene(name);
			});
		}

		void GameManager::setInitialScene(std::wstring name)
		{
			_opBuffer.queueOperation([&, name]() {
				_game->setInitialScene(name);
			});
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