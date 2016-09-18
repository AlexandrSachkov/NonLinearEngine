#include "NL_ImguiGameEditor.h"
#include "NL_ThreadLocal.h"
#include "NL_IGameManager.h"
#include "NL_Game.h"

#include <imgui.h>

namespace NLE
{
	namespace UI
	{
		ImguiGameEditor::ImguiGameEditor() :
			_visible(false),
			_nameBuff(256)
		{
		}

		ImguiGameEditor::~ImguiGameEditor()
		{
		}

		bool& ImguiGameEditor::getVisibility()
		{
			return _visible;
		}

		void ImguiGameEditor::draw(GAME::IGameManager& gameManager, Size2D screenSize)
		{
			if (!_visible)
				return;

			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;
			windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::Begin("Game Editor", &_visible, windowFlags);

			auto gameName = TLS::strConverter.local().to_bytes(gameManager.getGame().getName());
			_nameBuff.setText(gameName);

			ImGuiInputTextFlags flags = 0;
			flags |= ImGuiInputTextFlags_CallbackCompletion;
			flags |= ImGuiInputTextFlags_CallbackAlways;

			ImGui::InputText("Name", &_nameBuff[0], _nameBuff.getSize(), flags, [](ImGuiTextEditCallbackData* data) {
				std::string name(data->Buf);
				auto& gameManager = *static_cast<NLE::GAME::IGameManager*>(data->UserData);
				gameManager.getGame().setName(TLS::strConverter.local().from_bytes(name));
				return 0;
			}, (void*)&gameManager);

			ImGui::End();
		}
	}
}