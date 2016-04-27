#include "NL_Game.h"
#include "NL_Uuid.h"

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
	}
}