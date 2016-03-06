#ifndef NL_SYSTEM_SERVICES_H_
#define NL_SYSTEM_SERVICES_H_

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
			INPUT::IInputProcessor* input,
			GRAPHICS::IRenderingEngine* graphics,
			UI::IUiManager* ui,
			SCRIPT::IScriptingEngine* script
			) :
			input(input),
			graphics(graphics),
			ui(ui),
			script(script)
		{
		}

		~SystemServices()
		{
		}

		INPUT::IInputProcessor const* input;
		GRAPHICS::IRenderingEngine const* graphics;
		UI::IUiManager const* ui;
		SCRIPT::IScriptingEngine const* script;
	};
}

#endif
