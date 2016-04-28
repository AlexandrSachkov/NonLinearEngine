#include "NL_GameManager.h"

#include "NL_RenderingEngine.h"
#include "NL_UiManager.h"
#include "NL_ScriptingEngine.h"
#include "NL_Game.h"
#include "NL_Scene.h"
#include "NL_ThreadLocal.h"

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
			_game = new Game();
			_currentScene = new Scene();
			_game->_initialScene = _currentScene->_name;

			_commandBuffer.addFunction(COMMAND::QUIT_GAME,		[&](COMMAND::Data data) { _execStatus = TERMINATE; });
			_commandBuffer.addFunction(COMMAND::RESTART_GAME,	[&](COMMAND::Data data) { _execStatus = RESTART; });

			_commandBuffer.addFunction(COMMAND::LOAD_GAME,		[&](COMMAND::Data data) {
				TLS::StringConverter::reference converter = TLS::strConverter.local();
				std::wstring path = converter.from_bytes(data.name);

				_file.readAsync(path + L".nlegame", [=](std::vector<char>* data) {
					Game* game = _serializer.deserialize<Game>(data, SERIALIZATION::JSON);
					delete data;
					COMMAND::Data updateData;
					updateData.game = game;
					_commandBuffer.queueCommand(COMMAND::UPDATE_GAME, updateData);
					updateData.name = (char*)game->_initialScene.c_str();
					_commandBuffer.queueCommand(COMMAND::LOAD_SCENE, updateData);

				}, [=]() {
					eServices.console->push(CONSOLE::ERR, L"Failed to load game " + path);
				});
			});

			_commandBuffer.addFunction(COMMAND::UPDATE_GAME, [&](COMMAND::Data data) {
				delete _game;
				_game = data.game;
			});

			_commandBuffer.addFunction(COMMAND::LOAD_SCENE, [&](COMMAND::Data data) {
				TLS::StringConverter::reference converter = TLS::strConverter.local();
				std::wstring path = converter.from_bytes(data.name);

				_file.readAsync(path + L".nlescene", [=](std::vector<char>* data) {
					Scene* scene = _serializer.deserialize<Scene>(data, SERIALIZATION::JSON);
					delete data;
					COMMAND::Data updateData;
					updateData.scene = scene;
					_commandBuffer.queueCommand(COMMAND::UPDATE_SCENE, updateData);

				}, [=]() {
					eServices.console->push(CONSOLE::ERR, L"Failed to load scene " + path);
				});
			});

			_commandBuffer.addFunction(COMMAND::UPDATE_SCENE, [&](COMMAND::Data data) {
				delete _currentScene;
				_currentScene = data.scene;
			});

			_commandBuffer.addFunction(COMMAND::SAVE_GAME, [&](COMMAND::Data data) {
				auto* gameData = _serializer.serialize<Game>(data.game, SERIALIZATION::JSON);

				_file.writeAsync(data.game->getName() + L".nlegame", gameData, [=](std::vector<char>* serializedData) {
					delete serializedData;
					eServices.console->push(CONSOLE::STANDARD, L"Successfully saved game " + data.game->getName());

				}, [=](std::vector<char>* serializedData) {
					delete serializedData;
					eServices.console->push(CONSOLE::ERR, L"Failed to save game " + data.game->getName());
				});
			});

			_commandBuffer.addFunction(COMMAND::SAVE_SCENE, [&](COMMAND::Data data) {
				auto* sceneData = _serializer.serialize<Scene>(data.scene, SERIALIZATION::JSON);

				_file.writeAsync(data.scene->getName() + L".nlescene", sceneData, [=](std::vector<char>* serializedData) {
					delete serializedData;
					eServices.console->push(CONSOLE::STANDARD, L"Successfully saved scene " + data.scene->getName());

				}, [=](std::vector<char>* serializedData) {
					delete serializedData;
					eServices.console->push(CONSOLE::ERR, L"Failed to save scene " + data.scene->getName());
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