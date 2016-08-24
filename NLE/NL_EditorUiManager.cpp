#include "NL_EditorUiManager.h"
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
		EditorUiManager::EditorUiManager(EngineServices& eServices, CONSOLE::IConsoleQueue* consoleQueue) :
			_eServices(eServices),
			_consoleQueue(consoleQueue)
		{
		}

		EditorUiManager::~EditorUiManager()
		{
		}

		bool EditorUiManager::initialize()
		{
			return true;
		}

		void EditorUiManager::update(SystemServices* sServices, double deltaT)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			DATA::SharedData& data = _eServices.data->getData();
			auto& execTimes = data.sysExecutionTimes.get();

			/*std::wstring executionTimes =
				L"Execution times: \n"
				L"Input Processor: " + std::to_wstring(execTimes[INPUT_PROCESSOR]) + L"\n"
				L"Game Manager: " + std::to_wstring(execTimes[GAME_MANAGER]) + L"\n"
				L"Rendering Engine: " + std::to_wstring(execTimes[RENDERING_ENGINE]) + L"\n"
				L"UI Manager: " + std::to_wstring(execTimes[UI_MANAGER]) + L"\n"
				L"Scripting Engine: " + std::to_wstring(execTimes[SCRIPTING_ENGINE]) + L"\n"
				L"Data Manager: " + std::to_wstring(execTimes[DATA_MANAGER]) + L"\n"
				;

			_eServices.console->push(CONSOLE::DEBUG, executionTimes);

			std::pair<CONSOLE::OUTPUT_TYPE, std::wstring> consoleEntry;
			while (_consoleQueue->pop(consoleEntry))
			{
				std::wcout << consoleEntry.second << std::endl;
			}*/

			
			data.sysExecutionTimes.set(UI_MANAGER,timer.deltaT());
		}
	}
}