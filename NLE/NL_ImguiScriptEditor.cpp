#include "NL_ImguiScriptEditor.h"
#include "NL_ThreadLocal.h"

#include <imgui.h>

namespace NLE
{
	namespace UI
	{
		ImguiScriptEditor::ImguiScriptEditor() :
			_visible(false),
			_onUpdate([](std::wstring scriptName, std::wstring script) {}),
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
			std::wstring scriptName,
			std::wstring script,
			std::function<void(std::wstring scriptName, std::wstring script)> onUpdate,
			std::function<std::wstring()> getContext)
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

			_currentScriptName.setText(TLS::strConverter.local().to_bytes(scriptName));
			_currentScript.setText(TLS::strConverter.local().to_bytes(script));

			_visible = true;
		}

		void ImguiScriptEditor::draw(CONSOLE::IConsoleQueue& consoleQueue)
		{
			if (!_visible)
				return;

			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;

			std::wstring windowTitle = L"Script Editor: " + _getContext();
			ImGui::Begin(TLS::strConverter.local().to_bytes(windowTitle).c_str(), &_visible, windowFlags);
			ImGui::InputText("Name", &_currentScriptName[0], _currentScriptName.getSize(), 0);
			if (ImGui::Button("Update")) {
				std::wstring scriptName = TLS::strConverter.local().from_bytes(_currentScriptName.getText());
				std::wstring script = TLS::strConverter.local().from_bytes(_currentScript.getText());
				_originalScriptName = scriptName;
				_originalScript = script;
				_onUpdate(scriptName, script);	
			}
			ImGui::SameLine();
			if (ImGui::Button("Reset")) {
				_currentScriptName.setText(TLS::strConverter.local().to_bytes(_originalScriptName));
				_currentScript.setText(TLS::strConverter.local().to_bytes(_originalScript));
			}
			ImGui::InputTextMultiline("", &_currentScript[0], _currentScript.getSize(), ImVec2(-1.0f, -1.0f), ImGuiInputTextFlags_AllowTabInput);
			ImGui::End();
		}
	}
}