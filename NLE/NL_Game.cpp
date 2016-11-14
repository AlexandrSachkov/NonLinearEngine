#include "NL_Game.h"
#include "NL_Uuid.h"
#include "NL_ThreadLocal.h"
#include "NL_GameManager.h"

#include <filesystem>

namespace NLE
{
	namespace GAME
	{
		Game::Game() : Game (nullptr, nullptr)
		{
		}

		Game::Game(GameManager* gameManager, CONSOLE::IConsoleQueue_EService* console) :
			_gameManager(gameManager),
			_scriptingContext(this),
			_console(console)
		{
			_name = L"Game1";
			_initialScene = L"";
		}

		Game::~Game()
		{

		}

		GameManager* Game::getGameManager()
		{
			return _gameManager;
		}

		void Game::setGameManager(GameManager& gameManager)
		{
			_gameManager = &gameManager;
		}

		void Game::attachConsole(CONSOLE::IConsoleQueue_EService* console)
		{
			_console = console;
		}

		std::wstring Game::getName()
		{
			return _name;
		}

		void Game::setName(std::wstring name)
		{
			_name = name;
		}

		void Game::setInitialScene(std::wstring sceneName)
		{
			std::wstring scene;
			if (_scenes.get(sceneName, scene))
			{
				_initialScene = sceneName;
				_console->push(CONSOLE::STANDARD, L"Initial scene is set to " + sceneName);
			}
			else
			{
				_console->push(CONSOLE::ERR, L"Cannot set initial scene to " + sceneName + L". The provided scene is not found");
			}
		}

		std::wstring Game::getInitialScene()
		{
			return _initialScene;
		}

		void Game::addScene(std::wstring name, std::wstring path)
		{
			if (std::experimental::filesystem::exists(path))
			{
				_scenes.insert(name, path);
				_console->push(CONSOLE::STANDARD, L"Added scene " + path + L" as name " + name);
			}
			else
			{
				_console->push(CONSOLE::ERR, L"Cannot add scene " + name + L". No scene found at " + path);
			}
		}

		void Game::removeScene(std::wstring name)
		{
			_scenes.erase(name);
			if (_initialScene.compare(name) == 0)
			{
				_initialScene = L"";
			}
		}

		bool Game::getScenePath(std::wstring name, std::wstring& path)
		{
			if (_scenes.get(name, path))
				return true;
			return false;
		}

		std::vector<std::pair<std::wstring, std::wstring>> Game::getScenes()
		{
			std::vector<std::pair<std::wstring, std::wstring>> scenes;
			for (auto kv : _scenes.getData()) {
				scenes.push_back(kv);
			}
			return scenes;
		}

		SCRIPT::ScriptingContext& Game::getScriptingContext()
		{
			return _scriptingContext;
		}

		void Game::bind(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
		{
			binding.addVariableRef<Game>("this", this);
		}
	}
}