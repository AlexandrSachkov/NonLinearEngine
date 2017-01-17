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
			_name = "Game1";
			_initialScene = "";
		}

		Game::~Game()
		{

		}

		void Game::attachConsole(CONSOLE::IConsoleQueue_EServiceSP console)
		{
			_console = console;
		}

		std::string Game::getName()
		{
			return _name;
		}

		void Game::setName(std::string name)
		{
			_name = name;
		}

		void Game::setInitialScene(std::string sceneName)
		{
			std::string scene;
			if (_scenes.get(sceneName, scene))
			{
				_initialScene = sceneName;
				_console->push(CONSOLE::STANDARD, "Initial scene is set to " + sceneName);
			}
			else
			{
				_console->push(CONSOLE::ERR, "Cannot set initial scene to " + sceneName + ". The provided scene is not found");
			}
		}

		std::string Game::getInitialScene()
		{
			return _initialScene;
		}

		void Game::addScene(std::string name, std::string path)
		{
			if (std::experimental::filesystem::exists(path))
			{
				_scenes.insert(name, path);
				_console->push(CONSOLE::STANDARD, "Added scene " + path + " as name " + name);
			}
			else
			{
				_console->push(CONSOLE::ERR, "Cannot add scene " + name + ". No scene found at " + path);
			}
		}

		void Game::removeScene(std::string name)
		{
			if (_scenes.erase(name))
			{
				if (_initialScene.compare(name) == 0)
				{
					_initialScene = "";
				}
				_console->push(CONSOLE::STANDARD, "Removed scene " + name);
			}
			else
			{
				_console->push(CONSOLE::ERR, "Cannot remove scene " + name + ". The scene could not be found.");
			}
		}

		std::string Game::getScenePath(std::string name)
		{
			std::string scene;
			if (_scenes.get(name, scene))
			{
				return scene;
			}
			else
			{
				_console->push(CONSOLE::ERR, "The path for " + name + " could not be found. No such scene.");
				return "";
			}			
		}

		std::unordered_map<std::string, std::string> Game::getScenes()
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