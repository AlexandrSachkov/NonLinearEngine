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

#include <vector>
#include <iostream>
#include "tbb/tbb.h"

int main(void)
{
	NLE::ExecStatus execStatus = NLE::TERMINATE;

	do
	{
		NLE::TASK::TaskScheduler* taskScheduler = new NLE::TASK::TaskScheduler();
		NLE::CONSOLE::ConsoleQueue* consoleQueue = new NLE::CONSOLE::ConsoleQueue();
		NLE::EngineServices* engineServices = new NLE::EngineServices(consoleQueue, taskScheduler);

		NLE::INPUT::InputProcessor* inputProcessor = new NLE::INPUT::InputProcessor(*engineServices);
		NLE::GRAPHICS::RenderingEngine* renderingEngine = new NLE::GRAPHICS::RenderingEngine(*engineServices);
		NLE::UI::UiManager* uiManager = new NLE::UI::UiManager(*engineServices);
		NLE::SCRIPT::ScriptingEngine* scriptingEngine = new NLE::SCRIPT::ScriptingEngine(*engineServices);

		std::vector<NLE::ISystem*> parallelSystems;
		parallelSystems.push_back(renderingEngine);
		parallelSystems.push_back(uiManager);
		parallelSystems.push_back(scriptingEngine);

		NLE::DataManager* dataManager = new NLE::DataManager();
		NLE::SystemServices* systemServices = new NLE::SystemServices(inputProcessor, renderingEngine, uiManager, scriptingEngine);

		if (!inputProcessor->initialize())
			break;
		if (!renderingEngine->initialize())
			break;
		if (!uiManager->initialize())
			break;
		if (!scriptingEngine->initialize())
			break;

		taskScheduler->dispatchTasks();

		NLE::Timer inputTimer;
		NLE::Timer systemsTimer;

		do
		{
			inputTimer.sample();
			inputProcessor->update(*systemServices, *dataManager, inputTimer.getDeltaT());
			execStatus = inputProcessor->getExecutionStatus();

			systemsTimer.sample();
			tbb::parallel_for(
				tbb::blocked_range<size_t>(0, parallelSystems.size(), 1),
				[&](const tbb::blocked_range<size_t>& r)
			{
				for (uint_fast32_t i = (uint_fast32_t)r.begin(); i < r.end(); ++i)
				{
					parallelSystems[i]->update(*systemServices, *dataManager, systemsTimer.getDeltaT());
				}
			});

			dataManager->update();
			taskScheduler->dispatchTasks();

			std::cout << "Input Processor time: " << dataManager->in.inputProcessorTime << std::endl;
			std::cout << "Rendering Engine time: " << dataManager->in.renderingEngineTime << std::endl;
			std::cout << "UI Manager time: " << dataManager->in.uiManagerTime << std::endl;
			std::cout << "Scripting Engine time: " << dataManager->in.scriptingEngineTime << std::endl;

		} while (execStatus == NLE::CONTINUE);

		taskScheduler->waitOnTasks();		

		delete systemServices;
		delete dataManager;

		delete scriptingEngine;
		delete uiManager;
		delete renderingEngine;
		delete inputProcessor;

		delete engineServices;
		delete consoleQueue;
		delete taskScheduler;

		NLE::INPUT::GLOBAL_EVENT_QUEUE->clear();

	} while (execStatus == NLE::RESTART);
	return 0;
}

