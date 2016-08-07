#include "NL_RenderingEngine.h"

#include "NL_IGameManager.h"
#include "NL_IInputProcessor.h"
#include "NL_ThreadLocal.h"
#include "NL_GlfwWindowManager.h"

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

		bool RenderingEngine::initialize()
		{
			if (!_windowManager->initialize(Size2D(1024, 768), false, true, L"NonLinear Engine"))
				return false;
			return true;
		}

		void RenderingEngine::update(SystemServices* sServices, DataManager* data, double deltaT)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			_windowManager->pollEvents();
			//std::cout<< deltaT << std::endl;

			data->out.renderingEngineTime = timer.deltaT();
		}

		void RenderingEngine::setWindowTitle(std::wstring title)
		{
			_windowManager->setTitle(title);
		}

		void RenderingEngine::setResolution(Size2D resolution)
		{
			_resolution = resolution;
		}

		void RenderingEngine::setFullscreen(bool fullscreen)
		{
			_fullscreen = fullscreen;
		}
	}
}