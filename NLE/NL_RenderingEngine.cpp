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
		}

		RenderingEngine::~RenderingEngine()
		{			
		}

		bool RenderingEngine::initialize()
		{				
			return true;
		}

		void RenderingEngine::attachGetUIRenderingData(std::function<void*()> func)
		{

		}

		void RenderingEngine::update(SystemServices& sServices, double deltaT)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();
			
			DATA::SharedData& data = _eServices.data->getData();
			data.sysExecutionTimes.set(RENDERING_ENGINE, timer.deltaT());
		}
	}
}