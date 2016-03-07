#ifndef NL_SYSTEM_SERVICES_H_
#define NL_SYSTEM_SERVICES_H_

#include "NL_IGameManager.h"
#include "NL_IInputProcessor.h"
#include "NL_IRenderingEngine.h"
#include "NL_IUiManager.h"
#include "NL_IScriptingEngine.h"

namespace NLE
{
	class SystemServices
	{
	public:
		SystemServices(
			GAME::IGameManager* const game,
			INPUT::IInputProcessor* const input,
			GRAPHICS::IRenderingEngine* const graphics,
			UI::IUiManager* const ui,
			SCRIPT::IScriptingEngine* const script
			) :
			game(game),
			input(input),
			graphics(graphics),
			ui(ui),
			script(script)
		{
		}

		~SystemServices()
		{
		}

		GAME::IGameManager* const game;
		INPUT::IInputProcessor* const input;
		GRAPHICS::IRenderingEngine* const graphics;
		UI::IUiManager* const ui;
		SCRIPT::IScriptingEngine* const script;
	};
}

#endif
