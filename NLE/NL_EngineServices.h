#ifndef NL_ENGINE_SERVICES_H_
#define NL_ENGINE_SERVICES_H_

#include "NL_IConsoleQueue.h"
#include "NL_ITaskScheduler.h"

namespace NLE
{
	class EngineServices
	{
	public:
		EngineServices(CONSOLE::IConsoleQueue* console, TASK::ITaskScheduler* task) :
			console(console),
			task(task)
		{
		}

		~EngineServices()
		{
		}

		CONSOLE::IConsoleQueue* const console;
		TASK::ITaskScheduler* const task;
	};
}

#endif