#ifndef NL_SYSTEM_SERVICES_H_
#define NL_SYSTEM_SERVICES_H_

#include "NL_IGameManager.h"
#include "NL_IInputProcessor.h"
#include "NL_IRenderingEngine.h"
#include "NL_IScriptingEngine.h"

namespace NLE
{
	class SystemServices
	{
	public:
		SystemServices(
			GAME::IGameManager* game,
			INPUT::IInputProcessor* input,
			GRAPHICS::IRenderingEngine* graphics,
			SCRIPT::IScriptingEngine* script
			) :
			game(game),
			input(input),
			graphics(graphics),
			script(script)
		{
		}

		~SystemServices()
		{
		}

		GAME::IGameManager* const game;
		INPUT::IInputProcessor* const input;
		GRAPHICS::IRenderingEngine* const graphics;
		SCRIPT::IScriptingEngine* const script;
	};
}

#endif
