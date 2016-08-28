#include "NL_ImguiEditorUiManager.h"
#include "NL_ThreadLocal.h"
#include "NL_EngineServices.h"
#include "NL_SharedData.h"
#include "NL_SystemServices.h"
#include "NL_InputEvents.h"
#include "NL_ImguiInputMap.h"

#include <imgui.h>

#include <assert.h>
#include <string>
#include <iostream>
#include <algorithm>

namespace NLE
{
	namespace UI
	{
		ImguiEditorUiManager::ImguiEditorUiManager(
			EngineServices& eServices,
			CONSOLE::IConsoleQueue& consoleQueue,
			IWindowManager& windowManager,
			GAME::IGameManager& gameManager,
			INPUT::IInputProcessor& inputProcessor,
			GRAPHICS::IRenderingEngine& renderingEngine,
			SCRIPT::IScriptingEngine& scriptingEngine)
			:
			_eServices(eServices),
			_consoleQueue(consoleQueue),
			_windowManager(windowManager),
			_gameManager(gameManager),
			_inputProcessor(inputProcessor),
			_renderingEngine(renderingEngine),
			_scriptingEngine(scriptingEngine)
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

		void ImguiEditorUiManager::update(SystemServices* sServices, double deltaT, Size2D screenSize)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			DATA::SharedData& data = _eServices.data->getData();
			ImGuiIO& io = ImGui::GetIO();

			io.DisplaySize = ImVec2((float)screenSize.width, (float)screenSize.height);
			io.DeltaTime = (float)(deltaT * 0.000000001);

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

			//Need crossplatform implementation
			// Hide OS mouse cursor if ImGui is drawing it
			//SetCursor(io.MouseDrawCursor ? NULL : LoadCursor(NULL, IDC_ARROW));

			ImGui::NewFrame();

			bool show_test_window = true;
			bool show_another_window = false;
			ImVec4 clear_col = ImColor(114, 144, 154);

			// 1. Show a simple window
			// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
			{
				static float f = 0.0f;
				ImGui::Text("Hello, world!");
				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
				ImGui::ColorEdit3("clear color", (float*)&clear_col);
				if (ImGui::Button("Test Window")) show_test_window ^= 1;
				if (ImGui::Button("Another Window")) show_another_window ^= 1;
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			// 2. Show another simple window, this time using an explicit Begin/End pair
			if (show_another_window)
			{
				ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
				ImGui::Begin("Another Window", &show_another_window);
				ImGui::Text("Hello");
				ImGui::End();
			}

			// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
			if (show_test_window)
			{
				ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);     // Normally user code doesn't need/want to call it because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
				ImGui::ShowTestWindow(&show_test_window);
			}
			ImGui::Render();

			data.sysExecutionTimes.set(UI_MANAGER, timer.deltaT());
		}

		void ImguiEditorUiManager::show(bool show)
		{

		}
	}
}