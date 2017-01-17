#include "NL_ResourceManager.h"

#include "NL_FileIOManager.h"

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

		GAME::Game* ResourceManager::createGame()
		{
			return new GAME::Game(_eServices.console);
		}

		GAME::Scene* ResourceManager::createScene()
		{
			return new GAME::Scene();
		}

		GAME::GameObject* ResourceManager::createGameObject()
		{
			return new GAME::GameObject();
		}

		GAME::Game* ResourceManager::createGameFromFile(std::string path)
		{
			std::vector<char>* data = _eServices.file->read(path);
			if (data)
			{
				GAME::Game* game = _eServices.serializer->deserialize<GAME::Game>(data);
				delete data;
				_eServices.console->push(CONSOLE::STANDARD, "Successfully loaded game: " + path);
				return game;
			}
			else
			{
				_eServices.console->push(CONSOLE::ERR, "Failed to load game: " + path);
				return createGame();
			}
		}

		GAME::Scene* ResourceManager::createSceneFromFile(std::string path)
		{
			std::vector<char>* data = _eServices.file->read(path);
			if (data)
			{
				GAME::Scene* scene = _eServices.serializer->deserialize<GAME::Scene>(data);
				delete data;
				_eServices.console->push(CONSOLE::STANDARD, "Successfully loaded scene: " + path);
				return scene;
			}
			else
			{
				_eServices.console->push(CONSOLE::ERR, "Failed to load scene: " + path);
				return createScene();
			}
		}

		GAME::GameObject* ResourceManager::createGameObjectFromFile(std::string path)
		{
			return nullptr;
		}
	}
}