#ifndef NL_ENGINE_SERVICES_H_
#define NL_ENGINE_SERVICES_H_

#include "NL_IConsoleQueue.h"
#include "NL_ITaskScheduler.h"
#include "NL_IResourceManager.h"

namespace NLE
{
	class EngineServices
	{
	public:
		EngineServices(
			CONSOLE::IConsoleQueue_EService* console, 
			TASK::ITaskScheduler_EService* task
			) :
			console(console),
			task(task)
		{
		}

		~EngineServices()
		{
		}

		CONSOLE::IConsoleQueue_EService* const console;
		TASK::ITaskScheduler_EService* const task;
	};
}

#endif