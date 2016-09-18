#include "NL_ImguiSceneEditor.h"
#include "NL_ThreadLocal.h"
#include "NL_IGameManager.h"
#include "NL_Scene.h"

#include <imgui.h>

namespace NLE
{
	namespace UI
	{
		ImguiSceneEditor::ImguiSceneEditor() :
			_visible(false),
			_nameBuff(256)
		{
		}

		ImguiSceneEditor::~ImguiSceneEditor()
		{
		}

		bool& ImguiSceneEditor::getVisibility()
		{
			return _visible;
		}

		void ImguiSceneEditor::draw(GAME::IGameManager& gameManager, Size2D screenSize)
		{
			if (!_visible)
				return;

			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;
			windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::Begin("Scene Editor", &_visible, windowFlags);

			auto sceneName = TLS::strConverter.local().to_bytes(gameManager.getCurrentScene().getName());
			_nameBuff.setText(sceneName);

			ImGuiInputTextFlags flags = 0;
			flags |= ImGuiInputTextFlags_CallbackCompletion;
			flags |= ImGuiInputTextFlags_CallbackAlways;

			ImGui::InputText("Name", &_nameBuff[0], _nameBuff.getSize(), flags, [](ImGuiTextEditCallbackData* data) {
				std::string name(data->Buf);
				auto& gameManager = *static_cast<NLE::GAME::IGameManager*>(data->UserData);
				gameManager.getCurrentScene().setName(TLS::strConverter.local().from_bytes(name));
				return 0;
			}, (void*)&gameManager);

			ImGui::End();
		}
	}
}