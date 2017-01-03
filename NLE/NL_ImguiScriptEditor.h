#ifndef NL_IMGUI_SCRIPT_EDITOR_H_
#define NL_IMGUI_SCRIPT_EDITOR_H_

#include "NL_IConsoleQueue.h"
#include "NL_CharBuffer.h"

#include <string>
#include <functional>


namespace NLE
{
	namespace CONSOLE
	{

	}
	namespace UI
	{
		class ImguiScriptEditor
		{
		public:
			ImguiScriptEditor();
			~ImguiScriptEditor();

			bool& getVisibility();

			void editScript(
				std::wstring scriptName, 
				std::wstring script, 
				std::function<void(std::wstring scriptName, std::wstring script)> onUpdate,
				std::function<std::wstring()> getContext,
				std::function<std::wstring()> getErrorString);

			void draw(const CONSOLE::IConsoleQueueSP& consoleQueue, float textOpaqueness);
		private:
			bool _visible;
			std::wstring _originalScriptName;
			std::wstring _originalScript;
			std::function<void(std::wstring scriptName, std::wstring script)> _onUpdate;
			std::function<std::wstring()> _getContext;
			std::function<std::wstring()> _getErrorString;
			CharBuffer _currentScriptName;
			CharBuffer _currentScript;
		};
	}
}

#endif