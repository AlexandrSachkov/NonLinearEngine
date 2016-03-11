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
			CONSOLE::IConsoleQueue* console, 
			TASK::ITaskScheduler* task,
			RESOURCE::IResourceManager* resource
			) :
			console(console),
			task(task),
			resource(resource)
		{
		}

		~EngineServices()
		{
		}

		CONSOLE::IConsoleQueue* const console;
		TASK::ITaskScheduler* const task;
		RESOURCE::IResourceManager* const resource;
	};
}

#endif