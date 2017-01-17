#ifndef NL_ENGINE_SERVICES_H_
#define NL_ENGINE_SERVICES_H_

#include "NL_IConsoleQueue.h"
#include "NL_ITaskScheduler.h"
#include "NL_IResourceManager.h"
#include "NL_IDataManager.h"
#include "NL_IFileIOManager.h"
#include "NL_ISerializer.h"

namespace NLE
{
	class EngineServices
	{
	public:
		EngineServices(
			CONSOLE::IConsoleQueue_EServiceSP console, 
			TASK::ITaskScheduler_EServiceSP task,
			DATA::IDataManager_EServiceSP data,
			IO::IFileIOManager_EServiceSP file,
			SERIALIZATION::ISerializerSP serializer
			) :
			console(console),
			task(task),
			data(data),
			file(file),
			serializer(serializer)
		{
		}

		~EngineServices()
		{
		}

		CONSOLE::IConsoleQueue_EServiceSP console;
		TASK::ITaskScheduler_EServiceSP task;
		DATA::IDataManager_EServiceSP data;
		IO::IFileIOManager_EServiceSP file;
		SERIALIZATION::ISerializerSP serializer;
	};
}

#endif