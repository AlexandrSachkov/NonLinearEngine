#include "NL_GameManager.h"
#include "NL_InputProcessor.h"
#include "NL_RenderingEngine.h"
#include "NL_UiManager.h"
#include "NL_ScriptingEngine.h"

#include "NL_TaskScheduler.h"
#include "NL_ConsoleQueue.h"
#include "NL_DataManager.h"
#include "NL_SystemServices.h"
#include "NL_EngineServices.h"
#include "NL_Timer.h"
#include "NL_Globals.h"
#include "NL_FileIOManager.h"
#include "NL_ResourceManager.h"

#include <vector>
#include <iostream>
#include "tbb/tbb.h"

namespace NLE
{
	static void run()
	{
		ExecStatus execStatus = TERMINATE;

		do
		{
			TASK::TaskScheduler* taskScheduler = new TASK::TaskScheduler();
			CONSOLE::ConsoleQueue* consoleQueue = new CONSOLE::ConsoleQueue();
			IO::FileIOManager* fileIOManager = new IO::FileIOManager(consoleQueue, taskScheduler);
			RESOURCE::ResourceManager* resourceManager = new RESOURCE::ResourceManager(*fileIOManager);
			EngineServices* engineServices = new EngineServices(consoleQueue, taskScheduler, resourceManager);
			DataManager* dataManager = new DataManager();

			INPUT::InputProcessor* inputProcessor = new INPUT::InputProcessor(*engineServices);
			GRAPHICS::RenderingEngine* renderingEngine = new GRAPHICS::RenderingEngine(*engineServices);
			UI::UiManager* uiManager = new UI::UiManager(*engineServices);			
			SCRIPT::ScriptingEngine* scriptingEngine = new SCRIPT::ScriptingEngine(*engineServices);	

			if (!inputProcessor->initialize())
				break;
			if (!renderingEngine->initialize())
				break;
			if (!uiManager->initialize())
				break;
			if (!scriptingEngine->initialize())
				break;

			GAME::GameManager* gameManager = new GAME::GameManager(
				*engineServices, *fileIOManager, renderingEngine, uiManager, scriptingEngine);
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
				inputProcessor->update(*systemServices, *dataManager, inputTimer.deltaT());

				double systemTime = systemsTimer.deltaT();
				tbb::parallel_for(
					tbb::blocked_range<size_t>(0, parallelSystems.size(), 1),
					[&](const tbb::blocked_range<size_t>& r)
				{
					for (uint_fast32_t i = (uint_fast32_t)r.begin(); i < r.end(); ++i)
					{
						parallelSystems[i]->update(*systemServices, *dataManager, systemTime);
					}
				});

				dataManager->update();
				gameManager->update(*systemServices, *dataManager, gameTimer.deltaT());
				taskScheduler->dispatchTasks();

				execStatus = gameManager->getExecutionStatus();
			} while (execStatus == CONTINUE);

			taskScheduler->waitOnTasks();
			
			delete systemServices;			
			delete gameManager;
			delete scriptingEngine;
			delete uiManager;
			delete renderingEngine;
			delete inputProcessor;
			
			delete dataManager;
			delete engineServices;
			delete resourceManager;
			delete fileIOManager;
			delete consoleQueue;
			delete taskScheduler;

			INPUT::GLOBAL_EVENT_QUEUE->clear();

		} while (execStatus == RESTART);
	}
}


int main(int argc, char* argv[])
{
	NLE::run();
	return 0;
}

