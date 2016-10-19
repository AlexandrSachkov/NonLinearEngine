#include "NL_Game.h"
#include "NL_Uuid.h"
#include "NL_ThreadLocal.h"
#include "NL_GameManager.h"

namespace NLE
{
	namespace GAME
	{
		Game::Game() : Game (nullptr)
		{
		}

		Game::Game(GameManager* gameManager) :
			_gameManager(gameManager),
			_scriptingContext(this)
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

		void Game::bind(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
		{
			binding.addVariableRef<Game>("this", this);
		}
	}
}