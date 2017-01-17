#ifndef NL_IMGUI_SCRIPT_VIEWER_H_
#define NL_IMGUI_SCRIPT_VIEWER_H_

#include "NL_IConsoleQueue.h"

#include <functional>

namespace NLE
{
	namespace SCRIPT
	{
		class ScriptingContext;
	}
	namespace UI
	{
		class ImguiScriptEditor;
		class ImguiScriptViewer
		{
		public:
			ImguiScriptViewer();
			~ImguiScriptViewer();

			void draw(
				const CONSOLE::IConsoleQueueSP& consoleQueue,
				ImguiScriptEditor& scriptEditor,
				std::function<SCRIPT::ScriptingContext&()> getScriptingContext,
				std::function<std::string()> getContext
				);

		private:
			int _selectedScript;
		};
	}
}

#endif