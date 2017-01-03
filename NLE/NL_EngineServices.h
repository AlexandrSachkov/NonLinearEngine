#ifndef NL_ENGINE_SERVICES_H_
#define NL_ENGINE_SERVICES_H_

#include "NL_IConsoleQueue.h"
#include "NL_ITaskScheduler.h"
#include "NL_IResourceManager.h"
#include "NL_IDataManager.h"

namespace NLE
{
	class EngineServices
	{
	public:
		EngineServices(
			CONSOLE::IConsoleQueue_EServiceSP console, 
			TASK::ITaskScheduler_EServiceSP task,
			DATA::IDataManagerSP data
			) :
			console(console),
			task(task),
			data(data)
		{
		}

		~EngineServices()
		{
		}

		CONSOLE::IConsoleQueue_EServiceSP console;
		TASK::ITaskScheduler_EServiceSP task;
		DATA::IDataManagerSP data;
	};
}

#endif