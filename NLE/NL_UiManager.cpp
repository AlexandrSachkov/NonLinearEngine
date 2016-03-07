#include "NL_UiManager.h"
#include "NL_ThreadLocal.h"

#include "lua.hpp"

#include <assert.h>
#include <string>

namespace NLE
{
	namespace UI
	{
		UiManager::UiManager(EngineServices& eServices) :
			_eServices(eServices)
		{
		}

		UiManager::~UiManager()
		{
		}

		bool UiManager::initialize()
		{
			return true;
		}

		void UiManager::update(SystemServices& sServices, DataManager& data, double deltaT)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			data.out.uiManagerTime = timer.deltaT();
		}
	}
}