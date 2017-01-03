#include "NL_ImguiScriptViewer.h"
#include "NL_ScriptingContext.h"
#include "NL_ImguiScriptEditor.h"

#include <imgui.h>

namespace NLE
{
	namespace UI
	{
		ImguiScriptViewer::ImguiScriptViewer() :
			_selectedScript(0)
		{
		}

		ImguiScriptViewer::~ImguiScriptViewer()
		{
		}

		void ImguiScriptViewer::draw(
			const CONSOLE::IConsoleQueueSP& consoleQueue,
			ImguiScriptEditor& scriptEditor,
			std::function<SCRIPT::ScriptingContext&()> getScriptingContext,
			std::function<std::wstring()> getContext
			)
		{
			if (ImGui::CollapsingHeader("Scripts"))
			{
				auto scripts = getScriptingContext().getScripts();
				std::vector<std::string> scriptNames(scripts.size());
				for (int i = 0; i < scripts.size(); ++i)
				{
					scriptNames[i] = TLS::strConverter.local().to_bytes(scripts[i].first);
				}

				if (ImGui::Button("New")) {
					scriptEditor.editScript(
						L"Untitled",
						L"",
						[&, getScriptingContext](std::wstring scriptName, std::wstring script) {
						getScriptingContext().addScript(scriptName, script);
					}, 
					getContext,
						[&]() {
						return L"";
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("Delete")) {
					std::wstring selectedScriptName = scripts[_selectedScript].first;
					if (selectedScriptName.compare(SCRIPT::ON_INIT) == 0
						|| selectedScriptName.compare(SCRIPT::ON_UPDATE) == 0
						|| selectedScriptName.compare(SCRIPT::ON_EXIT) == 0)
					{
						consoleQueue->push(CONSOLE::WARNING, selectedScriptName + L" is a system script and cannot be deleted.");
					}
					else
					{
						getScriptingContext().removeScript(selectedScriptName);
						if (_selectedScript > 0)
							--_selectedScript;
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Edit")) {
					std::wstring selectedScriptName = scripts[_selectedScript].first;
					scriptEditor.editScript(
						selectedScriptName,
						getScriptingContext().getScript(selectedScriptName),
						[&, selectedScriptName, getScriptingContext](std::wstring scriptName, std::wstring script) {
						if (selectedScriptName.compare(scriptName) != 0)
						{
							getScriptingContext().removeScript(selectedScriptName);
						}
						getScriptingContext().addScript(scriptName, script);
					},
					getContext,
						[&, selectedScriptName, getScriptingContext]() {
						return getScriptingContext().getScriptErrorMessage(selectedScriptName);
					});
				}

				ImGui::ListBox("", &_selectedScript, [](void* vec, int index, const char** out_text) {
					auto& vector = *static_cast<std::vector<std::string>*>(vec);
					if (index < 0 || index >= (int)vector.size())
						return false;

					*out_text = vector[index].c_str();
					return true;
				}, static_cast<void*>(&scriptNames), (int)scripts.size());
			}
		}
	}
}