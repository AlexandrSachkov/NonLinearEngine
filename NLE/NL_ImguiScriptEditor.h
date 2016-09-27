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
				std::function<std::wstring()> getContext);

			void draw(CONSOLE::IConsoleQueue& consoleQueue);
		private:
			bool _visible;
			std::wstring _originalScriptName;
			std::wstring _originalScript;
			std::function<void(std::wstring scriptName, std::wstring script)> _onUpdate;
			std::function<std::wstring()> _getContext;
			CharBuffer _currentScriptName;
			CharBuffer _currentScript;
		};
	}
}

#endif