#include "NL_ImguiSceneViewer.h"
#include "NL_IGameManager.h"
#include "NL_Game.h"
#include "NL_ThreadLocal.h"

#include <imgui.h>
#include <filesystem>

namespace NLE
{
	namespace UI
	{
		ImguiSceneViewer::ImguiSceneViewer() :
			_sceneNameBuff(256),
			_scenePathBuff(1024),
			_showAddSceneDialog(false),
			_selectedScene(0)
		{
		}

		ImguiSceneViewer::~ImguiSceneViewer()
		{
		}

		void ImguiSceneViewer::draw(const GAME::IGameManagerSP& gameManager)
		{
			if (ImGui::CollapsingHeader("Scenes"))
			{
				auto scenes = gameManager->getGame().getScenes();
				std::vector<std::string> sceneNames(scenes.size());
				for (int i = 0; i < scenes.size(); ++i)
				{
					sceneNames[i] = TLS::strConverter.local().to_bytes(scenes[i].first);
				}

				if (ImGui::Button("New")) {
					gameManager->newScene();
				}
				ImGui::SameLine();
				if (ImGui::Button("Add")) {
					_showAddSceneDialog = true;
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove")) {
					if (scenes.size() > 0)
					{
						std::wstring selectedSceneName = scenes[_selectedScene].first;
						gameManager->removeScene(selectedSceneName);
						if (_selectedScene > 0)
							--_selectedScene;
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Load")) {
					if (scenes.size() > 0)
					{
						std::wstring selectedSceneName = scenes[_selectedScene].first;
						gameManager->loadSceneByName(selectedSceneName);
					}
				}

				ImGui::SameLine();
				if (ImGui::Button("Set As Initial")) {
					if (scenes.size() > 0)
					{
						std::wstring selectedSceneName = scenes[_selectedScene].first;
						gameManager->setInitialScene(selectedSceneName);
					}
				}

				std::wstring initialSceneName = gameManager->getGame().getInitialScene();
				if (initialSceneName.compare(L"") != 0)
				{
					std::string initialSceneMsg = "Initial Scene: " + TLS::strConverter.local().to_bytes(initialSceneName);
					ImGui::Text(initialSceneMsg.c_str());
				}

				ImGui::PushID(2);
				ImGui::ListBox("", &_selectedScene, [](void* vec, int index, const char** out_text) {
					auto& vector = *static_cast<std::vector<std::string>*>(vec);
					if (index < 0 || index >= (int)vector.size())
						return false;

					*out_text = vector[index].c_str();
					return true;
				}, static_cast<void*>(&sceneNames), (int)scenes.size());
				ImGui::PopID();
			}

			if (_showAddSceneDialog)
			{
				ImGui::OpenPopup("Add Scene");
				if (ImGui::BeginPopup("Add Scene"))
				{
					if (_scenePathBuff.isEmpty())
					{
						auto path = std::experimental::filesystem::current_path();
						_scenePathBuff.setText(path.generic_string());
					}
					ImGui::Text("Add Scene");
					ImGui::InputText("Name", &_sceneNameBuff[0], _sceneNameBuff.getSize(), 0, nullptr, (void*)this);
					ImGui::InputText("Path", &_scenePathBuff[0], _scenePathBuff.getSize(), 0, nullptr, (void*)this);
					if (ImGui::Button("Add", ImVec2(120, 0))) {
						ImGui::CloseCurrentPopup();
						_showAddSceneDialog = false;
						auto sceneName = TLS::strConverter.local().from_bytes(_sceneNameBuff.getText());
						auto scenePath = TLS::strConverter.local().from_bytes(_scenePathBuff.getText());
						gameManager->addScene(sceneName, scenePath);
					}
					ImGui::SameLine();
					if (ImGui::Button("Cancel", ImVec2(120, 0))) {
						ImGui::CloseCurrentPopup();
						_showAddSceneDialog = false;
					}
					ImGui::EndPopup();
				}
			}
		}
	}
}