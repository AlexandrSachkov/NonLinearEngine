#pragma once

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
				std::string scriptName, 
				std::string script, 
				std::function<void(std::string scriptName, std::string script)> onUpdate,
				std::function<std::string()> getContext,
				std::function<std::string()> getErrorString);

			void draw(const CONSOLE::IConsoleQueueSP& consoleQueue, float textOpaqueness);
		private:
			bool _visible;
			std::string _originalScriptName;
			std::string _originalScript;
			std::function<void(std::string scriptName, std::string script)> _onUpdate;
			std::function<std::string()> _getContext;
			std::function<std::string()> _getErrorString;
			CharBuffer _currentScriptName;
			CharBuffer _currentScript;
		};
	}
}