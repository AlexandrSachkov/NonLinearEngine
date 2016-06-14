#include "NL_Game.h"
#include "NL_Uuid.h"
#include "NL_ThreadLocal.h"

namespace NLE
{
	namespace GAME
	{
		Game::Game()
		{
			_name = L"Game1";
			_initialScene = L"";
			_testNum = UUID::generateUuid();
		}

		Game::~Game()
		{

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
			_initialScene = sceneName;
		}

		std::wstring Game::getInitialScene()
		{
			return _initialScene;
		}

		SCRIPT::ScriptingContext& Game::getScriptingContext()
		{
			return _scriptingContext;
		}
	}
}