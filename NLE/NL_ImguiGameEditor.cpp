#include "NL_ImguiGameEditor.h"
#include "NL_ThreadLocal.h"
#include "NL_IGameManager.h"
#include "NL_Game.h"
#include "NL_ScriptingContext.h"
#include "NL_ImguiScriptEditor.h"

#include <imgui.h>

namespace NLE
{
	namespace UI
	{
		ImguiGameEditor::ImguiGameEditor() :
			_visible(false),
			_nameBuff(256),
			_selectedScript(0)
		{
		}

		ImguiGameEditor::~ImguiGameEditor()
		{
		}

		bool& ImguiGameEditor::getVisibility()
		{
			return _visible;
		}

		void ImguiGameEditor::draw(
			const CONSOLE::IConsoleQueueSP& consoleQueue,
			const GAME::IGameManagerSP& gameManager,
			Size2D screenSize,
			ImguiScriptEditor& scriptEditor
			)
		{
			if (!_visible)
				return;

			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;
			windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::Begin("Game Editor", &_visible, windowFlags);

			_nameBuff.setText(gameManager->getGame().getName());

			ImGuiInputTextFlags flags = 0;
			flags |= ImGuiInputTextFlags_CallbackCompletion;
			flags |= ImGuiInputTextFlags_CallbackAlways;

			ImGui::InputText("Name", &_nameBuff[0], _nameBuff.getSize(), flags, [](ImGuiTextEditCallbackData* data) {
				std::string name(data->Buf);
				auto& gameManager = *static_cast<NLE::GAME::IGameManager*>(data->UserData);
				gameManager.getGame().setName(name);
				return 0;
			}, (void*)&gameManager);

			_scriptViewer.draw(
				consoleQueue, 
				scriptEditor, 
				[&]() ->SCRIPT::ScriptingContext& { return gameManager->getGame().getScriptingContext(); },
				[&]() { return gameManager->getGame().getName(); 
			});

			_sceneViewer.draw(gameManager);

			ImGui::End();
		}
	}
}