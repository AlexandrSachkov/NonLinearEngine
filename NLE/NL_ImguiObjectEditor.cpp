#include "NL_ImguiObjectEditor.h"
#include "NL_ThreadLocal.h"
#include "NL_IGameManager.h"
#include "NL_GameObject.h"

#include <imgui.h>

namespace NLE
{
	namespace UI
	{
		ImguiObjectEditor::ImguiObjectEditor() :
			_visible(false),
			_nameBuff(256)
		{
		}

		ImguiObjectEditor::~ImguiObjectEditor()
		{
		}

		bool& ImguiObjectEditor::getVisibility()
		{
			return _visible;
		}

		void ImguiObjectEditor::draw(GAME::IGameManager& gameManager, Size2D screenSize)
		{
			if (!_visible)
				return;

			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;
			windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::Begin("Object Editor", &_visible, windowFlags);

			ImGui::End();
		}
	}
}