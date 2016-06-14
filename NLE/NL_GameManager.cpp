#include "NL_GameManager.h"

#include "NL_RenderingEngine.h"
#include "NL_UiManager.h"
#include "NL_ScriptingEngine.h"
#include "NL_Game.h"
#include "NL_Scene.h"
#include "NL_ThreadLocal.h"
#include "NL_GameObject.h"

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
			_scriptingEngine(scriptingEngine),
			_serializationForm(SERIALIZATION::JSON)
		{
			_execStatus = ExecStatus::CONTINUE;
			_game = new Game();
			_currentScene = new Scene();
			_game->setInitialScene(_currentScene->getName());

			_commandBuffer.addFunction(COMMAND::QUIT_GAME,		[&](COMMAND::Data data) { _execStatus = TERMINATE; });
			_commandBuffer.addFunction(COMMAND::RESTART_GAME,	[&](COMMAND::Data data) { _execStatus = RESTART; });

			_commandBuffer.addFunction(COMMAND::LOAD_GAME,		[&](COMMAND::Data data) {
				std::wstring path = TLS::strConverter.local().from_bytes(data.name);

				_file.readAsync(path + L".nlegame", [=](std::vector<char>* data) {
					Game* game = _serializer.deserialize<Game>(data, _serializationForm);
					delete data;
					COMMAND::Data updateData;
					updateData.game = game;
					_commandBuffer.queueCommand(COMMAND::UPDATE_GAME, updateData);
					updateData.name = (char*)game->getInitialScene().c_str();
					_commandBuffer.queueCommand(COMMAND::LOAD_SCENE, updateData);

				}, [=]() {
					eServices.console->push(CONSOLE::ERR, L"Failed to load game " + path);
				});
			});

			_commandBuffer.addFunction(COMMAND::UPDATE_GAME, [&](COMMAND::Data data) {
				auto& ex = TLS::scriptExecutor.local();

				ex.bindContext(&_game->getScriptingContext());
				ex.executeContextScript(SCRIPT::ON_EXIT);
				delete _game;
				_game = data.game;

				ex.bindContext(&_game->getScriptingContext());
				ex.executeContextScript(SCRIPT::ON_INIT);
			});

			_commandBuffer.addFunction(COMMAND::LOAD_SCENE, [&](COMMAND::Data data) {
				std::wstring path = TLS::strConverter.local().from_bytes(data.name);

				_file.readAsync(path + L".nlescene", [=](std::vector<char>* data) {
					Scene* scene = _serializer.deserialize<Scene>(data, _serializationForm);
					delete data;
					COMMAND::Data updateData;
					updateData.scene = scene;
					_commandBuffer.queueCommand(COMMAND::UPDATE_SCENE, updateData);

				}, [=]() {
					eServices.console->push(CONSOLE::ERR, L"Failed to load scene " + path);
				});
			});

			_commandBuffer.addFunction(COMMAND::UPDATE_SCENE, [&](COMMAND::Data data) {
				auto& ex = TLS::scriptExecutor.local();

				ex.bindContext(&_currentScene->getScriptingContext());
				ex.executeContextScript(SCRIPT::ON_EXIT);
				delete _currentScene;
				_currentScene = data.scene;
				
				ex.bindContext(&_currentScene->getScriptingContext());
				ex.executeContextScript(SCRIPT::ON_INIT);
			});

			_commandBuffer.addFunction(COMMAND::SAVE_GAME, [&](COMMAND::Data data) {
				auto* gameData = _serializer.serialize<Game>(data.game, _serializationForm);

				_file.writeAsync(data.game->getName() + L".nlegame", gameData, [=](std::vector<char>* serializedData) {
					delete serializedData;
					eServices.console->push(CONSOLE::STANDARD, L"Successfully saved game " + data.game->getName());

				}, [=](std::vector<char>* serializedData) {
					delete serializedData;
					eServices.console->push(CONSOLE::ERR, L"Failed to save game " + data.game->getName());
				});
			});

			_commandBuffer.addFunction(COMMAND::SAVE_SCENE, [&](COMMAND::Data data) {
				auto* sceneData = _serializer.serialize<Scene>(data.scene, _serializationForm);

				_file.writeAsync(data.scene->getName() + L".nlescene", sceneData, [=](std::vector<char>* serializedData) {
					delete serializedData;
					eServices.console->push(CONSOLE::STANDARD, L"Successfully saved scene " + data.scene->getName());

				}, [=](std::vector<char>* serializedData) {
					delete serializedData;
					eServices.console->push(CONSOLE::ERR, L"Failed to save scene " + data.scene->getName());
				});
			});

			_commandBuffer.addFunction(COMMAND::ADD_OBJECT, [&](COMMAND::Data data) {
				_currentScene->addObject(new GameObject());
			});

			_commandBuffer.addFunction(COMMAND::UPDATE_OBJECT, [&](COMMAND::Data data) {
				_currentScene->addObject(data.gameObject);
			});

			_commandBuffer.addFunction(COMMAND::LOAD_OBJECT, [&](COMMAND::Data data) {
				std::wstring path = TLS::strConverter.local().from_bytes(data.name);

				_file.readAsync(path + L".nleobject", [=](std::vector<char>* data) {
					GameObject* object = _serializer.deserialize<GameObject>(data, _serializationForm);
					delete data;
					COMMAND::Data updateData;
					updateData.gameObject = object;
					_commandBuffer.queueCommand(COMMAND::UPDATE_OBJECT, updateData);
					
				}, [=]() {
					eServices.console->push(CONSOLE::ERR, L"Failed to load game object " + path);
				});
			});

			_commandBuffer.addFunction(COMMAND::SAVE_OBJECT, [&](COMMAND::Data data) {
				auto* objectData = _serializer.serialize<GameObject>(data.gameObject, _serializationForm);

				_file.writeAsync(data.scene->getName() + L".nleobject", objectData, [=](std::vector<char>* serializedData) {
					delete serializedData;
					eServices.console->push(CONSOLE::STANDARD, L"Successfully saved game object " + data.gameObject->getName());

				}, [=](std::vector<char>* serializedData) {
					delete serializedData;
					eServices.console->push(CONSOLE::ERR, L"Failed to save game object " + data.gameObject->getName());
				});
			});

		}

		GameManager::~GameManager()
		{
		}

		void GameManager::update(SystemServices& sServices, DataManager& data, double deltaT)
		{
			_commandBuffer.processCommands();
		}

		void GameManager::queueCommand(COMMAND::Type type, COMMAND::Data data)
		{
			_commandBuffer.queueCommand(type, data);
		}

		ExecStatus GameManager::getExecutionStatus()
		{
			return _execStatus;
		}
	}
}