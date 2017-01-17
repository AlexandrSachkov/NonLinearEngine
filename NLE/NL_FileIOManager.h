#pragma once

#include "NL_IFileIOManager.h"
#include "NL_Thread.h"
#include "NL_IConsoleQueue.h"
#include "NL_ITaskScheduler.h"

#include "tbb/concurrent_queue.h"

namespace NLE
{
	namespace IO
	{

		class FileIOManager : public IFileIOManager
		{
		public:
			FileIOManager(CONSOLE::IConsoleQueueSP console);
			~FileIOManager();
			
			std::vector<char>* read(std::string path);
			bool write(std::string path, std::vector<char>* srcData);

		private:			
			FileIOManager(FileIOManager const&) = delete;
			void operator=(FileIOManager const&) = delete;

			CONSOLE::IConsoleQueueSP _console;
		};
	}
	
}
