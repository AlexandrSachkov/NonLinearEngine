#include "NL_Game.h"
#include "NL_Uuid.h"
#include "NL_ThreadLocal.h"

namespace NLE
{
	namespace GAME
	{
		Game::Game()
		{
			_name = "Game1";
			_initialScene = "none";
			_testNum = UUID::generateUuid();
		}

		Game::~Game()
		{

		}

		std::wstring Game::getName()
		{
			TLS::StringConverter::reference converter = TLS::strConverter.local();
			return converter.from_bytes(_name);
		}
	}
}