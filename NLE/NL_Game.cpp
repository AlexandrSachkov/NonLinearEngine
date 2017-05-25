#include "NL_Game.h"
#include "NL_Uuid.h"
#include "NL_ThreadLocal.h"
#include "NL_GameManager.h"
#include "NL_ScriptingContext.h"

#include <filesystem>

namespace NLE
{
	namespace GAME
	{
		Game::Game(CONSOLE::IConsoleQueue_EServiceSP console, const GameDesc& desc) :
			_console(console),
			_scriptingContext(desc.scriptingContextDesc),
			_name(desc.name)
		{
		}

		Game::Game(const Game& other) :
			_console(other._console),
			_scriptingContext(other._scriptingContext),
			_name(other._name)
		{
		}

		Game& Game::operator=(const Game& other)
		{
			_console = other._console;
			_scriptingContext = other._scriptingContext;
			_name = other._name;
			return *this;
		}

		Game::~Game()
		{
		}

		GameDesc Game::getDesc()
		{
			GameDesc desc;
			desc.name = _name;
			desc.scriptingContextDesc = _scriptingContext.getDesc();
			return desc;
		}

		std::string Game::getName()
		{
			return _name;
		}

		void Game::setName(std::string name)
		{
			_name = name;
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