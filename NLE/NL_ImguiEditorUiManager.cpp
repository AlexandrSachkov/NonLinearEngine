#include "NL_ImguiEditorUiManager.h"
#include "NL_ThreadLocal.h"
#include "NL_EngineServices.h"
#include "NL_SharedData.h"

#include <assert.h>
#include <string>
#include <iostream>

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

		void ImguiEditorUiManager::update(SystemServices* sServices, double deltaT)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			DATA::SharedData& data = _eServices.data->getData();
			auto& execTimes = data.sysExecutionTimes.get();

			/*std::pair<CONSOLE::OUTPUT_TYPE, std::wstring> consoleEntry;
			while (_consoleQueue->pop(consoleEntry))
			{
				std::wcout << consoleEntry.second << std::endl;
			}*/

			
			data.sysExecutionTimes.set(UI_MANAGER,timer.deltaT());
		}

		void ImguiEditorUiManager::show(bool show)
		{

		}
	}
}