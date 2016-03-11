#ifndef NL_FILE_IO_MANAGER_H_
#define NL_FILE_IO_MANAGER_H_

#include "NL_Thread.h"
#include "NL_IConsoleQueue.h"
#include "NL_ITaskScheduler.h"

#include "tbb/concurrent_queue.h"

#include <string>
#include <vector>
#include <functional>

namespace NLE
{
	namespace IO
	{
		enum OperationType
		{
			READ,
			WRITE
		};

		struct FileIOOperationDesc
		{
			OperationType type;
			std::wstring path;
			std::vector<char>* inputData;
			std::function<void(std::vector<char>* data)> onSuccess;
			std::function<void()> onFailure;
		};
		

		class FileIOManager
		{
		public:
			FileIOManager(NLE::CONSOLE::IConsoleQueue* const console, NLE::TASK::ITaskScheduler* const taskScheduler);
			~FileIOManager();
			std::wstring getFileExtension(std::wstring path);
			void readAsync(
				std::wstring path, 
				std::function<void(std::vector<char>* data)> onSuccess, 
				std::function<void()> onFailure
				);

			void writeAsync(
				std::wstring path, 
				std::vector<char>* inputData, 
				std::function<void()> onSuccess, 
				std::function<void()> onFailure
				);

			bool read(std::wstring& path, std::vector<char>*& dataOut);
			bool write(std::wstring path, std::vector<char>* srcData);

		private:			
			FileIOManager(FileIOManager const&) = delete;
			void operator=(FileIOManager const&) = delete;

			NLE::CONSOLE::IConsoleQueue* const _console;
			NLE::TASK::ITaskScheduler* const _task;
			Core::Thread _loadingThread;
			tbb::concurrent_queue<FileIOOperationDesc> _fileOps;
		};
	}
	
}

#endif
