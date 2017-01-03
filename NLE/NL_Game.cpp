#include "NL_Game.h"
#include "NL_Uuid.h"
#include "NL_ThreadLocal.h"
#include "NL_GameManager.h"

#include <filesystem>

namespace NLE
{
	namespace GAME
	{
		Game::Game() : Game (nullptr)
		{
		}

		Game::Game(CONSOLE::IConsoleQueue_EServiceSP console) :
			_scriptingContext(this),
			_console(console)
		{
			_name = L"Game1";
			_initialScene = L"";
		}

		Game::~Game()
		{

		}

		IGameManager* Game::getGameManager()
		{
			return _gameManager;
		}

		void Game::setGameManager(IGameManager* gameManager)
		{
			_gameManager = gameManager;
		}

		void Game::attachConsole(CONSOLE::IConsoleQueue_EServiceSP console)
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
			if (_scenes.erase(name))
			{
				if (_initialScene.compare(name) == 0)
				{
					_initialScene = L"";
				}
				_console->push(CONSOLE::STANDARD, L"Removed scene " + name);
			}
			else
			{
				_console->push(CONSOLE::ERR, L"Cannot remove scene " + name + L". The scene could not be found.");
			}
		}

		std::wstring Game::getScenePath(std::wstring name)
		{
			std::wstring scene;
			if (_scenes.get(name, scene))
			{
				return scene;
			}
			else
			{
				_console->push(CONSOLE::ERR, L"The path for " + name + L" could not be found. No such scene.");
				return L"";
			}			
		}

		std::unordered_map<std::wstring, std::wstring> Game::getScenes()
		{
			return _scenes.getData();
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