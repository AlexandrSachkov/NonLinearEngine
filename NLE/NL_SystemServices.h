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
			GAME::IGameManagerSP game,
			INPUT::IInputProcessorSP input,
			GRAPHICS::IRenderingEngineSP graphics,
			SCRIPT::IScriptingEngineSP script
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

		GAME::IGameManagerSP game;
		INPUT::IInputProcessorSP input;
		GRAPHICS::IRenderingEngineSP graphics;
		SCRIPT::IScriptingEngineSP script;
	};
}

#endif
