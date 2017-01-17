#include "NL_ImguiScriptEditor.h"
#include "NL_ThreadLocal.h"

#include <imgui.h>

namespace NLE
{
	namespace UI
	{
		ImguiScriptEditor::ImguiScriptEditor() :
			_visible(false),
			_onUpdate([](std::string scriptName, std::string script) {}),
			_currentScriptName(256),
			_currentScript(16416)
		{
		}

		ImguiScriptEditor::~ImguiScriptEditor()
		{
		}

		bool& ImguiScriptEditor::getVisibility()
		{
			return _visible;
		}

		void ImguiScriptEditor::editScript(
			std::string scriptName,
			std::string script,
			std::function<void(std::string scriptName, std::string script)> onUpdate,
			std::function<std::string()> getContext,
			std::function<std::string()> getErrorString)
		{
			/*if (_currentScriptName.compare(_originalScriptName) != 0
				|| _currentScript.compare(_originalScript) != 0)
			{
				//issue save/discard dialog
			}*/
			_originalScriptName = scriptName;
			_originalScript = script;
			_onUpdate = onUpdate;
			_getContext = getContext;
			_getErrorString = getErrorString;

			_currentScriptName.setText(scriptName);
			_currentScript.setText(script);

			_visible = true;
		}

		void ImguiScriptEditor::draw(const CONSOLE::IConsoleQueueSP& consoleQueue, float textOpaqueness)
		{
			if (!_visible)
				return;

			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;

			std::string windowTitle = "Script Editor: " + _getContext();
			ImGui::Begin(windowTitle.c_str(), &_visible, windowFlags);
			ImGui::InputText("Name", &_currentScriptName[0], _currentScriptName.getSize(), 0);
			if (ImGui::Button("Update")) {
				std::string scriptName = _currentScriptName.getText();
				std::string script = _currentScript.getText();
				_originalScriptName = scriptName;
				_originalScript = script;
				_onUpdate(scriptName, script);	
			}
			ImGui::SameLine();
			if (ImGui::Button("Reset")) {
				_currentScriptName.setText(_originalScriptName);
				_currentScript.setText(_originalScript);
			}
			std::string error = _getErrorString();
			if (error.compare("") != 0)
			{
				ImGui::Text("Execution Error:");
				ImGui::SameLine();
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, textOpaqueness));
				ImGui::Text(error.c_str());
				ImGui::PopStyleColor();
			}
			ImGui::InputTextMultiline("", &_currentScript[0], _currentScript.getSize(), ImVec2(-1.0f, -1.0f), ImGuiInputTextFlags_AllowTabInput);
			ImGui::End();
		}
	}
}