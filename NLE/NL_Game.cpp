#include "NL_Game.h"
#include "NL_Uuid.h"
#include "NL_ThreadLocal.h"

namespace NLE
{
	namespace GAME
	{
		Game::Game() :
			_scriptingContext(this)
		{
			_name = L"Game1";
			_initialScene = L"";
		}

		Game::~Game()
		{

		}

		std::wstring Game::getName()
		{
			return _name;
		}

		std::string Game::getNameStr()
		{
			return TLS::strConverter.local().to_bytes(_name);
		}

		void Game::setName(std::wstring name)
		{
			_name = name;
		}

		void Game::setName(std::string name)
		{
			_name = TLS::strConverter.local().from_bytes(name);
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