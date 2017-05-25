#include "NL_ResourceManager.h"

#include "NL_FileIOManager.h"
#include "NL_Game.h"
#include "NL_Scene.h"
#include "NL_GameObject.h"

namespace NLE
{
	namespace RESOURCE
	{
		ResourceManager::ResourceManager(EngineServices eServices) :
			_eServices(eServices)
		{
		}

		ResourceManager::~ResourceManager()
		{
		}

		GAME::Game* ResourceManager::createGame(const GAME::GameDesc& desc)
		{
			return new GAME::Game(_eServices.console, desc);
		}

		GAME::Scene* ResourceManager::createScene(const GAME::SceneDesc& desc)
		{
			return new GAME::Scene(desc);
		}

		GAME::GameObject* ResourceManager::createGameObject()
		{
			return new GAME::GameObject();
		}

		std::tuple<bool, GAME::GameDesc> ResourceManager::loadGameDesc(std::string path)
		{
			GAME::GameDesc desc;
			std::vector<char>* data = _eServices.file->read(path);
			if (!data) {
				_eServices.console->push(CONSOLE::ERR, "Failed to load game: " + path);
				return std::make_tuple<>(false, desc);
			}

			_eServices.serializer->deserialize<GAME::GameDesc>(data, desc);
			delete data;
			_eServices.console->push(CONSOLE::STANDARD, "Successfully loaded game: " + path);
			return std::make_tuple<>(true, desc);
		}

		bool ResourceManager::saveGameDesc(std::string path, const GAME::GameDesc& desc)
		{
			auto* gameData = _eServices.serializer->serialize<GAME::GameDesc>(desc);
			if (_eServices.file->write(path, gameData))
			{
				delete gameData;
				_eServices.console->push(CONSOLE::STANDARD, "Successfully saved game: " + path);
				return true;
			}

			delete gameData;
			_eServices.console->push(CONSOLE::ERR, "Failed to save game: " + path);
			return false;
		}

		std::tuple<bool, GAME::SceneDesc> ResourceManager::loadSceneDesc(std::string path)
		{
			GAME::SceneDesc desc;
			std::vector<char>* data = _eServices.file->read(path);
			if (!data) {
				_eServices.console->push(CONSOLE::ERR, "Failed to load scene: " + path);
				return std::make_tuple<>(false, desc);
			}

			_eServices.serializer->deserialize<GAME::SceneDesc>(data, desc);
			delete data;
			_eServices.console->push(CONSOLE::STANDARD, "Successfully loaded scene: " + path);
			return std::make_tuple<>(true, desc);
		}

		bool ResourceManager::saveSceneDesc(std::string path, const GAME::SceneDesc& desc)
		{
			auto* sceneData = _eServices.serializer->serialize<GAME::SceneDesc>(desc);
			if (_eServices.file->write(path, sceneData))
			{
				delete sceneData;
				_eServices.console->push(CONSOLE::STANDARD, "Successfully saved scene: " + path);
				return true;
			}

			delete sceneData;
			_eServices.console->push(CONSOLE::ERR, "Failed to save scene: " + path);
			return false;
		}

		GAME::GameObject* ResourceManager::createGameObjectFromFile(std::string path)
		{
			return nullptr;
		}
	}
}