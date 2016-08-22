#include "NL_RenderingEngine.h"

#include "NL_IGameManager.h"
#include "NL_IInputProcessor.h"
#include "NL_ThreadLocal.h"
#include "NL_GlfwWindowManager.h"
#include "NL_EngineServices.h"
#include "NL_SharedData.h"

#include <iostream>

#include "lua.hpp"

namespace NLE
{
	namespace GRAPHICS
	{
		RenderingEngine::RenderingEngine(EngineServices& eServices) :
			_eServices(eServices)
		{
			_windowManager = new GlfwWindowManager(eServices.console);
		}

		RenderingEngine::~RenderingEngine()
		{			
			delete _windowManager;
		}

		bool RenderingEngine::initialize(Size2D screenResolution, bool fullscreen, bool decorated, std::wstring title)
		{				
			if (!_windowManager->initialize(screenResolution, fullscreen, decorated, title))
				return false;
			return true;
		}

		void RenderingEngine::update(SystemServices* sServices, double deltaT)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			_windowManager->pollEvents();
			
			DATA::SharedData& data = _eServices.data->getData();
			//data.sysExecutionTimes[RENDERING_ENGINE].set(timer.deltaT());
		}
	}
}