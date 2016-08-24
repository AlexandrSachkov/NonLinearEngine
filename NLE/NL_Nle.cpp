#include "NL_GameManager.h"
#include "NL_InputProcessor.h"

#if defined (RENDERING_API_D3D11)
	#include "NL_D3D11RenderingEngine.h"
#else
	#include "NL_RenderingEngine.h"
#endif

#include "NL_UiManager.h"
#include "NL_ScriptingEngine.h"

#include "NL_TBBTaskScheduler.h"
#include "NL_ConsoleQueue.h"
#include "NL_DataManager.h"
#include "NL_SystemServices.h"
#include "NL_EngineServices.h"
#include "NL_Timer.h"
#include "NL_Globals.h"
#include "NL_FileIOManager.h"
#include "NL_ResourceManager.h"
#include "NL_ISerializer.h"
#include "NL_GlfwWindowManager.h"

#include <vector>
#include <iostream>
#include "tbb/tbb.h"

namespace NLE
{
	static void run()
	{
		GAME::ExecStatus execStatus = GAME::TERMINATE;

		do
		{
			TASK::ITaskScheduler* taskScheduler = new TASK::TBBTaskScheduler();
			CONSOLE::IConsoleQueue* consoleQueue = CONSOLE::GLOBAL_CONSOLE_QUEUE;
			IO::IFileIOManager* fileIOManager = new IO::FileIOManager(consoleQueue, taskScheduler);
			SERIALIZATION::ISerializer* serializer = new SERIALIZATION::CerealSerializer(SERIALIZATION::JSON);
			//RESOURCE::ResourceManager* resourceManager = new RESOURCE::ResourceManager(*fileIOManager);
			DATA::IDataManager* dataManager = new DATA::DataManager();
			EngineServices engineServices(consoleQueue, taskScheduler, dataManager);

			Size2D windowSize(1024, 768);
			bool fullscreen = false;

			GlfwWindowManager* windowManager = new GlfwWindowManager(engineServices.console);
			if (!windowManager->initialize(windowSize, fullscreen, true, L"NonLinear Engine"))
				break;

			INPUT::InputProcessor* inputProcessor = new INPUT::InputProcessor(engineServices);
			if (!inputProcessor->initialize())
				break;

#if defined (RENDERING_API_D3D11)
			GRAPHICS::D3D11RenderingEngine* renderingEngine = new GRAPHICS::D3D11RenderingEngine(engineServices);
			if (!renderingEngine->initialize(windowManager->getWindowHandle(), windowSize, fullscreen))
				break;
#else
			GRAPHICS::RenderingEngine* renderingEngine = new GRAPHICS::RenderingEngine(engineServices);
			if (!renderingEngine->initialize())
				break;
#endif
			UI::IUiManager* uiManager = new UI::UiManager(engineServices, consoleQueue);		
			if (!uiManager->initialize())
				break;

			SCRIPT::IScriptingEngine* scriptingEngine = new SCRIPT::ScriptingEngine(engineServices);	
			if (!scriptingEngine->initialize())
				break;

			GAME::IGameManager* gameManager = new GAME::GameManager(
				engineServices, fileIOManager, *serializer, renderingEngine, uiManager, scriptingEngine);
			SystemServices* systemServices = new SystemServices(
				gameManager, inputProcessor, renderingEngine, uiManager, scriptingEngine);

			std::vector<ISystem*> parallelSystems;
			parallelSystems.push_back(renderingEngine);
			parallelSystems.push_back(uiManager);
			parallelSystems.push_back(scriptingEngine);
							
			Timer inputTimer, systemsTimer, gameTimer;
			taskScheduler->dispatchTasks();

			do
			{
				windowManager->pollEvents();
				inputProcessor->update(systemServices, inputTimer.deltaT());
				dataManager->syncData(taskScheduler->getNumThreads());
				gameManager->update(systemServices, gameTimer.deltaT());
				dataManager->syncData(taskScheduler->getNumThreads());

				double systemTime = systemsTimer.deltaT();
				tbb::parallel_for(
					tbb::blocked_range<size_t>(0, parallelSystems.size(), 1),
					[&](const tbb::blocked_range<size_t>& r)
				{
					for (uint_fast32_t i = (uint_fast32_t)r.begin(); i < r.end(); ++i)
					{
						parallelSystems[i]->update(systemServices, systemTime);
					}
				});

				dataManager->syncData(taskScheduler->getNumThreads());
				taskScheduler->dispatchTasks();

				execStatus = gameManager->getExecutionStatus();
			} while (execStatus == GAME::CONTINUE);

			taskScheduler->waitOnTasks();
			
			delete systemServices;			
			delete gameManager;
			delete scriptingEngine;
			delete uiManager;
			delete renderingEngine;
			delete inputProcessor;
			
			delete dataManager;
			//delete resourceManager;
			delete serializer;
			delete fileIOManager;
			delete taskScheduler;

			INPUT::GLOBAL_EVENT_QUEUE->clear();
			CONSOLE::GLOBAL_CONSOLE_QUEUE->clear();

		} while (execStatus == GAME::RESTART);
	}
}


int main(int argc, char* argv[])
{
	NLE::run();
	return 0;
}

