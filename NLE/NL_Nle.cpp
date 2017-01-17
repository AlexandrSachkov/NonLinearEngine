#include "NL_TBBTaskScheduler.h"
#include "NL_ConsoleQueue.h"
#include "NL_DataManager.h"
#include "NL_Globals.h"
#include "NL_FileIOManager.h"
#include "NL_ISerializer.h"
#include "NL_EngineServices.h"
#include "NL_CommonTypes.h"
#include "NL_GlfwWindowManager.h"
#include "NL_GameManager.h"
#include "NL_InputProcessor.h"

#if defined (RENDERING_API_D3D11)
	#include "NL_D3D11RenderingEngine.h"
#else
	#include "NL_RenderingEngine.h"
#endif

#include "NL_ScriptingEngine.h"
#include "NL_ImguiEditorUiManager.h"
#include "NL_SystemServices.h"
#include "NL_Timer.h"
#include "NL_ResourceManager.h"

#include <vector>
#include <iostream>
#include <memory>
#include "tbb/tbb.h"
#include <LuaIntf.h>

namespace NLE
{
	static void run()
	{
		GAME::ExecStatus execStatus = GAME::TERMINATE;

		do
		{
			SCRIPT::ScriptExecutor masterExecutor;
			SCRIPT::Bindings::attachMaster(masterExecutor.getState());
			auto scriptModule = LuaIntf::LuaBinding(masterExecutor.getState()).beginModule("nle");

			auto taskScheduler = std::make_shared<TASK::TBBTaskScheduler>();
			auto fileIOManager = std::make_shared<IO::FileIOManager>(CONSOLE::GLOBAL_CONSOLE_QUEUE);
			scriptModule.addVariableRef<IO::IFileIOManager_EService>("file", fileIOManager.get());

			auto serializer = std::make_shared<SERIALIZATION::CerealSerializer>(SERIALIZATION::JSON);
			auto dataManager = std::make_shared<DATA::DataManager>();
			EngineServices engineServices(CONSOLE::GLOBAL_CONSOLE_QUEUE, taskScheduler, dataManager, fileIOManager, serializer);

			auto resourceManager = std::make_shared<RESOURCE::ResourceManager>(engineServices);
			scriptModule.addVariableRef<RESOURCE::IResourceManager>("resource", resourceManager.get());

			Size2D windowSize(1920, 1080);
			bool fullscreen = false;

			auto windowManager = std::make_shared<GlfwWindowManager>(engineServices.console);
			if (!windowManager->initialize(windowSize, fullscreen, true, L"NonLinear Engine"))
				break;
			scriptModule.addVariableRef<IWindowManager>("windowManager", windowManager.get());

			auto inputProcessor = std::make_shared<INPUT::InputProcessor>(engineServices);
			if (!inputProcessor->initialize())
				break;

#if defined (RENDERING_API_D3D11)
			auto renderingEngine = std::make_shared<GRAPHICS::D3D11RenderingEngine>(engineServices);
			if (!renderingEngine->initialize(*windowManager))
				break;
#else
			auto renderingEngine = std::make_shared<GRAPHICS::RenderingEngine>(engineServices);
			if (!renderingEngine->initialize())
				break;
#endif

			auto scriptingEngine = std::make_shared<SCRIPT::ScriptingEngine>(engineServices);
			if (!scriptingEngine->initialize())
				break;

			auto gameManager = std::make_shared<GAME::GameManager>
				(engineServices, windowManager, fileIOManager, serializer, renderingEngine, scriptingEngine);			
			scriptModule.addVariableRef<GAME::GameManager>("gameManager", gameManager.get());

			auto editorUiManager = std::make_shared<UI::ImguiEditorUiManager>(
				engineServices, CONSOLE::GLOBAL_CONSOLE_QUEUE, windowManager, gameManager, inputProcessor, renderingEngine, scriptingEngine, masterExecutor);
			if (!editorUiManager->initialize())
				break;

			inputProcessor->attachKeyAndCharCallback([&](INPUT::Event event) {
				editorUiManager->queueKeyAndCharEvent(event);
			});
			renderingEngine->attachGetUIRenderingData([&]() {
				return (void*)editorUiManager->getDrawData();
			});

			scriptModule.endModule();

			SystemServices systemServices(gameManager, inputProcessor, renderingEngine, scriptingEngine);

			std::vector<ISystemSP> parallelSystems;
			parallelSystems.push_back(renderingEngine);
			parallelSystems.push_back(scriptingEngine);
							
			Timer inputTimer, systemsTimer, gameTimer, editorUiTimer;
			taskScheduler->dispatchTasks();
			
			do
			{
				windowManager->pollEvents();

				inputProcessor->update(systemServices, inputTimer.deltaT());
				dataManager->syncData(taskScheduler->getNumThreads());

				editorUiManager->update(systemServices, editorUiTimer.deltaT(), windowManager->getClientSize());
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
			
			//delete resourceManager;

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

