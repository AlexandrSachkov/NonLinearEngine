#include "NL_UiManager.h"
#include "NL_ThreadLocal.h"
#include "NL_EngineServices.h"

#include <assert.h>
#include <string>
#include <iostream>

namespace NLE
{
	namespace UI
	{
		UiManager::UiManager(EngineServices& eServices, CONSOLE::IConsoleQueue* consoleQueue) :
			_eServices(eServices),
			_consoleQueue(consoleQueue)
		{
		}

		UiManager::~UiManager()
		{
		}

		bool UiManager::initialize()
		{
			return true;
		}

		void UiManager::update(SystemServices* sServices, double deltaT)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			std::pair<CONSOLE::OUTPUT_TYPE, std::wstring> consoleEntry;
			while (_consoleQueue->pop(consoleEntry))
			{
				std::wcout << consoleEntry.second << std::endl;
			}

			//data->out.uiManagerTime = timer.deltaT();
		}
	}
}