#ifndef NL_FILE_IO_MANAGER_H_
#define NL_FILE_IO_MANAGER_H_

#include "NL_IFileIOManager.h"
#include "NL_Thread.h"
#include "NL_IConsoleQueue.h"
#include "NL_ITaskScheduler.h"

#include "tbb/concurrent_queue.h"

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
			std::function<void(std::vector<char>* data)> onFailure;
		};
		

		class FileIOManager : public IFileIOManager
		{
		public:
			FileIOManager(NLE::CONSOLE::IConsoleQueue* const console, NLE::TASK::ITaskScheduler* const taskScheduler);
			~FileIOManager();
			
			void readAsync(
				std::wstring path, 
				std::function<void(std::vector<char>* data)> onSuccess, 
				std::function<void()> onFailure
				);

			void writeAsync(
				std::wstring path, 
				std::vector<char>* inputData, 
				std::function<void(std::vector<char>* data)> onSuccess,
				std::function<void(std::vector<char>* data)> onFailure
				);

			bool read(std::wstring path, std::vector<char>*& dataOut);
			bool write(std::wstring path, std::vector<char>* srcData);

		private:			
			FileIOManager(FileIOManager const&) = delete;
			void operator=(FileIOManager const&) = delete;

			std::wstring getFileExtension(std::wstring path);

			NLE::CONSOLE::IConsoleQueue* const _console;
			NLE::TASK::ITaskScheduler* const _task;
			Core::Thread _loadingThread;
			tbb::concurrent_queue<FileIOOperationDesc> _fileOps;

		};
	}
	
}

#endif
