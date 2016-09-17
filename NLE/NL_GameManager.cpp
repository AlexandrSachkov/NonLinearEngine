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
				_game = new Game();
				_currentScene = new Scene();
				_game->setInitialScene(_currentScene->getName());
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

		void GameManager::updateGame(Game* game)
		{
			_opBuffer.queueOperation([&, game]() {
				auto& ex = TLS::scriptExecutor.local();

				ex.bindContext(&_game->getScriptingContext());
				ex.executeContextScript(SCRIPT::ON_EXIT);
				delete _game;
				_game = game;

				ex.bindContext(&_game->getScriptingContext());
				ex.executeContextScript(SCRIPT::ON_INIT);
			});
		}

		void GameManager::updateScene(Scene* scene)
		{
			_opBuffer.queueOperation([&, scene]() {
				auto& ex = TLS::scriptExecutor.local();

				ex.bindContext(&_currentScene->getScriptingContext());
				ex.executeContextScript(SCRIPT::ON_EXIT);
				delete _currentScene;
				_currentScene = scene;

				ex.bindContext(&_currentScene->getScriptingContext());
				ex.executeContextScript(SCRIPT::ON_INIT);
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
				_execStatus = TERMINATE;
			});
		}

		ExecStatus GameManager::getExecutionStatus()
		{
			return _execStatus;
		}
	}
}