#include "NL_ImguiEditorUiManager.h"
#include "NL_ThreadLocal.h"
#include "NL_EngineServices.h"
#include "NL_SharedData.h"
#include "NL_SystemServices.h"
#include "NL_InputEvents.h"
#include "NL_ImguiInputMap.h"
#include "NL_Game.h"
#include "NL_Scene.h"

#include <assert.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <experimental\filesystem>

namespace NLE
{
	namespace UI
	{
		ImguiEditorUiManager::ImguiEditorUiManager(
			EngineServices eServices,
			CONSOLE::IConsoleQueueSP consoleQueue,
			IWindowManagerSP windowManager,
			GAME::IGameManagerSP gameManager,
			INPUT::IInputProcessorSP inputProcessor,
			GRAPHICS::IRenderingEngineSP renderingEngine,
			SCRIPT::IScriptingEngineSP scriptingEngine)
			:
			_eServices(eServices),
			_consoleQueue(consoleQueue),
			_windowManager(windowManager),
			_gameManager(gameManager),
			_inputProcessor(inputProcessor),
			_renderingEngine(renderingEngine),
			_scriptingEngine(scriptingEngine),

			_showEditor(true),
			_showEditorSettings(false),
			_showConsole(true),
			_showSaveGameDialog(false),
			_showSaveSceneDialog(false),
			_showLoadGameDialog(false),
			_showLoadSceneDialog(false),

			_saveGameBuff(256),
			_saveSceneBuff(256),
			_loadGameBuff(1024),
			_loadSceneBuff(1024),

			_consoleLogs(100),

			_windowBgColor(0.0f, 0.0f, 0.0f, 0.392f),
			_textColor(0.0f, 1.0f, 1.0f, 1.0f),
			_borderColor(0.0f, 1.0f, 1.0f, 0.129f),
			_itemColor(0.0f, 0.435f, 0.796f, 0.392f),
			_itemHoverColor(0.0f, 0.675f, 0.820f, 0.263f),
			_itemActiveColor(0.0f, 0.384f, 0.620f, 0.690f),
			_selectionColor(0.290f, 0.290f, 0.290f, 0.690f),

			_commandBuffer(1024)
		{
		}

		ImguiEditorUiManager::~ImguiEditorUiManager()
		{
		}

		bool ImguiEditorUiManager::initialize()
		{
			return true;
		}

		int ImguiEditorUiManager::getScancodeForKeyEvent(INPUT::Event event)
		{
			assert(event.eventType == INPUT::EVENT_KEY);
			ImGuiIO& io = ImGui::GetIO();

			auto key = INPUT::NLEtoImguiKey(event.eventData.keyEvent.key);
			if (key == -1)
				return event.eventData.keyEvent.scancode;

			if (io.KeyMap[key] == -1)
				io.KeyMap[key] = event.eventData.keyEvent.scancode;

			return io.KeyMap[key];
		}

		ImDrawData* ImguiEditorUiManager::getDrawData()
		{
			return ImGui::GetDrawData();
		}

		void ImguiEditorUiManager::queueKeyAndCharEvent(INPUT::Event event)
		{
			_keyAndCharEvents.push(event);
		}

		void ImguiEditorUiManager::update(SystemServices& sServices, double deltaT, Size2D screenSize)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			DATA::SharedData& data = _eServices.data->getData();
			ImGuiIO& io = ImGui::GetIO();
			io.DisplaySize = ImVec2((float)screenSize.width, (float)screenSize.height);
			io.DeltaTime = (float)(deltaT * 0.000000001);

			//Need crossplatform implementation
			// Hide OS mouse cursor if ImGui is drawing it
			//SetCursor(io.MouseDrawCursor ? NULL : LoadCursor(NULL, IDC_ARROW));

			captureInput(deltaT, screenSize);
			ImGui::NewFrame();
			drawUI(screenSize);
			ImGui::Render();

			data.sysExecutionTimes.set(UI_MANAGER, timer.deltaT());
		}

		void ImguiEditorUiManager::captureInput(double deltaT, Size2D screenSize)
		{
			DATA::SharedData& data = _eServices.data->getData();
			ImGuiIO& io = ImGui::GetIO();

			io.MouseDown[0] = data.mouseButtonPressed.get()[INPUT::MOUSE_BUTTON_LEFT];
			io.MouseDown[1] = data.mouseButtonPressed.get()[INPUT::MOUSE_BUTTON_RIGHT];
			io.MouseDown[2] = data.mouseButtonPressed.get()[INPUT::MOUSE_BUTTON_MIDDLE];
			io.MouseWheel += (float)data.scrollOffset.get()[1];
			io.MousePos.x = (float)data.mouseCursorPosition.get()[0];
			io.MousePos.y = (float)data.mouseCursorPosition.get()[1];

			INPUT::Event event;
			while (_keyAndCharEvents.pop(event))
			{
				if (event.eventType == INPUT::EVENT_KEY)
				{
					int scancode = getScancodeForKeyEvent(event);
					io.KeysDown[scancode] = event.eventData.keyEvent.action == INPUT::ACTION_PRESS ? 1 : 0;
				}
				else
				{
					io.AddInputCharacter((unsigned short)event.eventData.charEvent.code);
				}
			}

			io.KeyCtrl = data.keyModsPressed.get()[INPUT::KEY_MOD_CONTROL];
			io.KeyShift = data.keyModsPressed.get()[INPUT::KEY_MOD_SHIFT];
			io.KeyAlt = data.keyModsPressed.get()[INPUT::KEY_MOD_ALT];
			io.KeySuper = data.keyModsPressed.get()[INPUT::KEY_MOD_SUPER];
		}

		void ImguiEditorUiManager::drawUI(Size2D screenSize)
		{
			/*ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoTitleBar;
			windowFlags |= ImGuiWindowFlags_NoResize;
			windowFlags |= ImGuiWindowFlags_NoMove;
			windowFlags |= ImGuiWindowFlags_NoScrollbar;
			windowFlags |= ImGuiWindowFlags_NoCollapse;
			windowFlags |= ImGuiWindowFlags_MenuBar;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

			ImGui::SetNextWindowPos(ImVec2(0,0));
			ImGui::SetNextWindowSize(ImVec2((float)screenSize.width, (float)screenSize.height), ImGuiSetCond_FirstUseEver);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			applyColorScheme(true);
			ImGui::Begin("Engine UI Overlay Window", &_showEditor, windowFlags);

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New Game", nullptr))
					{
						_gameManager->newGame();
					}
					if (ImGui::MenuItem("Load Game", nullptr))
					{
						_showLoadGameDialog = true;
					}
					if (ImGui::MenuItem("Load Scene", nullptr))
					{
						_showLoadSceneDialog = true;
					}
					if(ImGui::MenuItem("Save Game", nullptr))
					{
						_gameManager->saveGame({});
					}
					if (ImGui::MenuItem("Save Game As", nullptr))
					{
						_showSaveGameDialog = true;
					}
					if (ImGui::MenuItem("Save Scene", nullptr))
					{
						_gameManager->saveScene({});
					}
					if (ImGui::MenuItem("Save Scene As", nullptr))
					{
						_showSaveSceneDialog = true;
					}
					if (ImGui::MenuItem("Exit", nullptr))
					{
						_gameManager->quitGame();
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("View"))
				{
					ImGui::MenuItem("Editor", nullptr, &_showEditorSettings);
					ImGui::MenuItem("Game", nullptr, &_gameEditor.getVisibility());
					ImGui::MenuItem("Scene", nullptr, &_sceneEditor.getVisibility());
					ImGui::MenuItem("Object", nullptr, &_objectEditor.getVisibility());
					ImGui::MenuItem("Console", nullptr, &_showConsole);
					ImGui::EndMenu();
				}
				ImGui::SameLine(ImGui::GetWindowWidth() - 100);
				ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
				ImGui::EndMenuBar();
			}

			ImGui::End();
			restoreColorScheme();
			ImGui::PopStyleVar();
			
			if(_showEditorSettings)
				showEditorSettings(screenSize);
			
			if (_showConsole)
				showConsole(screenSize);

			if (_showSaveGameDialog)
				showSaveGameDialog(screenSize);

			if(_showSaveSceneDialog)
				showSaveSceneDialog(screenSize);

			if (_showLoadGameDialog)
				showLoadGameDialog(screenSize);

			if (_showLoadSceneDialog)
				showLoadSceneDialog(screenSize);

			if (_gameEditor.getVisibility())
				showGameEditor(screenSize);

			if (_sceneEditor.getVisibility())
				showSceneEditor(screenSize);

			if (_objectEditor.getVisibility())
				showObjectEditor(screenSize);

			if (_scriptEditor.getVisibility())
				showScriptEditor(screenSize);*/
			showCommandPrompt();
		}

		void ImguiEditorUiManager::showEditorSettings(Size2D screenSize)
		{
			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;
			windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::SetNextWindowPos(ImVec2((float)screenSize.width / 2, (float)screenSize.height / 2), ImGuiSetCond_FirstUseEver);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 2.0f);
			applyColorScheme(false);
			ImGui::Begin("Editor Settings", &_showEditorSettings, windowFlags);

			if (ImGui::CollapsingHeader("Color Scheme"))
			{
				ImGui::ColorEdit4("Window Background", (float*)&_windowBgColor);
				ImGui::ColorEdit4("Text", (float*)&_textColor);
				ImGui::ColorEdit4("Border", (float*)&_borderColor);
				ImGui::ColorEdit4("Item", (float*)&_itemColor);
				ImGui::ColorEdit4("Item Hover", (float*)&_itemHoverColor);
				ImGui::ColorEdit4("Item Active", (float*)&_itemActiveColor);
				ImGui::ColorEdit4("Selection", (float*)&_selectionColor);
			}

			ImGui::End();
			restoreColorScheme();
			ImGui::PopStyleVar();
		}

		void ImguiEditorUiManager::showConsole(Size2D screenSize)
		{
			std::pair<CONSOLE::OUTPUT_TYPE, std::wstring> consoleEntry;
			while (_consoleQueue->pop(consoleEntry))
			{
				auto& cnv = TLS::strConverter.local();
				auto entry = cnv.to_bytes(consoleEntry.second);
				_consoleLogs.push({ consoleEntry.first, entry });
			}

			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;

			ImGui::SetNextWindowPos(ImVec2((float)screenSize.width / 2, (float)screenSize.height / 2), ImGuiSetCond_FirstUseEver);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 2.0f);
			applyColorScheme(false);
			ImGui::Begin("Console", &_showConsole, windowFlags);

			ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
			ImGuiListClipper clipper((int)_consoleLogs.size());
			while (clipper.Step())
			{
				for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i)
				{
					auto entry = _consoleLogs[i];
					switch (entry.first)
					{
					case CONSOLE::STANDARD:
					case CONSOLE::DEBUG:
						ImGui::PushStyleColor(ImGuiCol_Text, _textColor);
						break;
					case CONSOLE::WARNING: 
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, _textColor.w));
						break;
					case CONSOLE::ERR:
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, _textColor.w));
						break;
					default:
						ImGui::PushStyleColor(ImGuiCol_Text, _textColor);
						break;
					}
					ImGui::TextUnformatted(entry.second.c_str());
					ImGui::PopStyleColor();
				}
			}
			//ImGui::SetScrollHere();
			ImGui::EndChild();

			ImGui::End();
			restoreColorScheme();
			ImGui::PopStyleVar();
		}

		void ImguiEditorUiManager::showSaveGameDialog(Size2D screenSize)
		{
			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;
			windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;

			applyColorScheme(false);
			ImGui::OpenPopup("Save Game");
			if (ImGui::BeginPopupModal("Save Game", NULL, windowFlags))
			{
				if (_saveGameBuff.isEmpty())
				{
					auto gameName = TLS::strConverter.local().to_bytes(_gameManager->getGame().getName());
					_saveGameBuff.setText(gameName);
				}
				ImGui::InputText("Name", &_saveGameBuff[0], _saveGameBuff.getSize(), 0, nullptr, (void*)this);
				if (ImGui::Button("Save", ImVec2(120, 0))) {
					ImGui::CloseCurrentPopup();
					_showSaveGameDialog = false;
					auto gameName = TLS::strConverter.local().from_bytes(_saveGameBuff.getText());
					_gameManager->saveGame(gameName);
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) {
					ImGui::CloseCurrentPopup();
					_showSaveGameDialog = false;
					auto gameName = TLS::strConverter.local().to_bytes(_gameManager->getGame().getName());
					_saveGameBuff.setText(gameName);
				}
				ImGui::EndPopup();
			}
			restoreColorScheme();
		}

		void ImguiEditorUiManager::showSaveSceneDialog(Size2D screenSize)
		{
			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;
			windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;

			applyColorScheme(false);
			ImGui::OpenPopup("Save Scene");
			if (ImGui::BeginPopupModal("Save Scene", NULL, windowFlags))
			{
				if (_saveSceneBuff.isEmpty())
				{
					auto sceneName = TLS::strConverter.local().to_bytes(_gameManager->getCurrentScene().getName());
					_saveSceneBuff.setText(sceneName);
				}
				ImGui::InputText("Name", &_saveSceneBuff[0], _saveSceneBuff.getSize(), 0, nullptr, (void*)this);
				if (ImGui::Button("Save", ImVec2(120, 0))) {
					ImGui::CloseCurrentPopup();
					_showSaveSceneDialog = false;
					auto sceneName = TLS::strConverter.local().from_bytes(_saveSceneBuff.getText());
					_gameManager->saveScene(sceneName);
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) {
					ImGui::CloseCurrentPopup();
					_showSaveSceneDialog = false;
					auto sceneName = TLS::strConverter.local().to_bytes(_gameManager->getCurrentScene().getName());
					_saveSceneBuff.setText(sceneName);
				}
				ImGui::EndPopup();
			}
			restoreColorScheme();
		}

		void ImguiEditorUiManager::showLoadGameDialog(Size2D screenSize)
		{
			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;
			windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;

			applyColorScheme(false);
			ImGui::OpenPopup("Load Game");
			if (ImGui::BeginPopupModal("Load Game", NULL, windowFlags))
			{
				if (_loadGameBuff.isEmpty())
				{
					auto path = std::experimental::filesystem::current_path();
					_loadGameBuff.setText(path.generic_string());
				}
				ImGui::InputText("Path", &_loadGameBuff[0], _loadGameBuff.getSize(), 0, nullptr, (void*)this);
				if (ImGui::Button("Load", ImVec2(120, 0))) {
					ImGui::CloseCurrentPopup();
					_showLoadGameDialog = false;
					auto gamePath = TLS::strConverter.local().from_bytes(_loadGameBuff.getText());
					_gameManager->loadGame(gamePath);
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) {
					ImGui::CloseCurrentPopup();
					_showLoadGameDialog = false;
				}
				ImGui::EndPopup();
			}
			restoreColorScheme();
		}

		void ImguiEditorUiManager::showLoadSceneDialog(Size2D screenSize)
		{
			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;
			windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;

			applyColorScheme(false);
			ImGui::OpenPopup("Load Scene");
			if (ImGui::BeginPopupModal("Load Scene", NULL, windowFlags))
			{
				if (_loadSceneBuff.isEmpty())
				{
					auto path = std::experimental::filesystem::current_path();
					_loadSceneBuff.setText(path.generic_string());
				}
				ImGui::InputText("Path", &_loadSceneBuff[0], _loadSceneBuff.getSize(), 0, nullptr, (void*)this);
				if (ImGui::Button("Load", ImVec2(120, 0))) {
					ImGui::CloseCurrentPopup();
					_showLoadSceneDialog = false;
					auto scenePath = TLS::strConverter.local().from_bytes(_loadSceneBuff.getText());
					_gameManager->loadScene(scenePath);
				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) {
					ImGui::CloseCurrentPopup();
					_showLoadSceneDialog = false;
				}
				ImGui::EndPopup();
			}
			restoreColorScheme();
		}

		void ImguiEditorUiManager::showGameEditor(Size2D screenSize)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 2.0f);
			applyColorScheme(false);
			ImGui::SetNextWindowPos(ImVec2((float)screenSize.width / 2, (float)screenSize.height / 2), ImGuiSetCond_FirstUseEver);

			_gameEditor.draw(_consoleQueue, _gameManager, screenSize, _scriptEditor);

			restoreColorScheme();
			ImGui::PopStyleVar();
		}

		void ImguiEditorUiManager::showSceneEditor(Size2D screenSize)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 2.0f);
			applyColorScheme(false);
			ImGui::SetNextWindowPos(ImVec2((float)screenSize.width / 2, (float)screenSize.height / 2), ImGuiSetCond_FirstUseEver);

			_sceneEditor.draw(_consoleQueue, _gameManager, screenSize, _scriptEditor);

			restoreColorScheme();
			ImGui::PopStyleVar();
		}

		void ImguiEditorUiManager::showObjectEditor(Size2D screenSize)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 2.0f);
			applyColorScheme(false);
			ImGui::SetNextWindowPos(ImVec2((float)screenSize.width / 2, (float)screenSize.height / 2), ImGuiSetCond_FirstUseEver);

			_objectEditor.draw(_gameManager, screenSize);

			restoreColorScheme();
			ImGui::PopStyleVar();
		}

		void ImguiEditorUiManager::showScriptEditor(Size2D screenSize)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 2.0f);
			applyColorScheme(false);
			ImGui::SetNextWindowPos(ImVec2((float)screenSize.width / 2, (float)screenSize.height / 2), ImGuiSetCond_FirstUseEver);

			_scriptEditor.draw(_consoleQueue, _textColor.w);

			restoreColorScheme();
			ImGui::PopStyleVar();
		}

		void ImguiEditorUiManager::applyColorScheme(bool root)
		{
			if(root)
				ImGui::PushStyleColor(ImGuiCol_WindowBg, ImColor(0.0f, 0.0f, 0.0f, 0.0f));
			else
				ImGui::PushStyleColor(ImGuiCol_WindowBg, _windowBgColor);

			ImGui::PushStyleColor(ImGuiCol_MenuBarBg, _windowBgColor);
			ImGui::PushStyleColor(ImGuiCol_Text, _textColor);
			ImGui::PushStyleColor(ImGuiCol_Border, _borderColor);
			ImGui::PushStyleColor(ImGuiCol_Button, _itemColor);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, _itemHoverColor);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, _itemActiveColor);
			ImGui::PushStyleColor(ImGuiCol_Header, _itemColor);
			ImGui::PushStyleColor(ImGuiCol_HeaderHovered, _itemHoverColor);
			ImGui::PushStyleColor(ImGuiCol_HeaderActive, _itemActiveColor);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, _itemColor);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, _itemHoverColor);
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, _itemActiveColor);
			ImGui::PushStyleColor(ImGuiCol_TitleBg, _itemColor);
			ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, _itemColor);
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, _itemActiveColor);
			ImGui::PushStyleColor(ImGuiCol_CloseButton, _itemColor);
			ImGui::PushStyleColor(ImGuiCol_CloseButtonHovered, _itemHoverColor);
			ImGui::PushStyleColor(ImGuiCol_CloseButtonActive, _itemActiveColor);
			ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, _selectionColor);
		}

		void ImguiEditorUiManager::restoreColorScheme()
		{
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}

		void ImguiEditorUiManager::show(bool show)
		{
			_showEditor = show;
		}

		void ImguiEditorUiManager::showCommandPrompt()
		{
			std::pair<CONSOLE::OUTPUT_TYPE, std::wstring> consoleEntry;
			while (_consoleQueue->pop(consoleEntry))
			{
				auto& cnv = TLS::strConverter.local();
				auto entry = cnv.to_bytes(consoleEntry.second);
				_consoleLogs.push({ consoleEntry.first, entry });
			}

			ImGuiWindowFlags windowFlags = 0;
			//windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;

			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 2.0f);
			applyColorScheme(false);
			ImGui::Begin("Command Prompt", &_showConsole, windowFlags);

			ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
			ImGuiListClipper clipper((int)_consoleLogs.size());
			while (clipper.Step())
			{
				for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i)
				{
					auto entry = _consoleLogs[i];
					switch (entry.first)
					{
					case CONSOLE::STANDARD:
					case CONSOLE::DEBUG:
						ImGui::PushStyleColor(ImGuiCol_Text, _textColor);
						break;
					case CONSOLE::WARNING:
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, _textColor.w));
						break;
					case CONSOLE::ERR:
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, _textColor.w));
						break;
					default:
						ImGui::PushStyleColor(ImGuiCol_Text, _textColor);
						break;
					}
					ImGui::TextUnformatted(entry.second.c_str());
					ImGui::PopStyleColor();
				}
			}

			ImGui::EndChild();

			ImGui::PushItemWidth(ImGui::GetWindowWidth() - 80);
			ImGui::InputText("", &_commandBuffer[0], _commandBuffer.getSize(), 0);
			ImGui::SameLine();
			if (ImGui::Button("Run", ImVec2(50, 0))) {
				auto& cnv = TLS::strConverter.local();
				auto entry = cnv.from_bytes(_commandBuffer.getText());
				_gameManager->executeScript(entry);
			}
			ImGui::End();
			restoreColorScheme();
			ImGui::PopStyleVar();
		}
	}
}