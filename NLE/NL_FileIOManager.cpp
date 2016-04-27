#include "NL_FileIOManager.h"
#include "NL_ThreadLocal.h"

#include <fstream>
#include <iostream>
#include <vector>

namespace NLE
{
	namespace IO
	{
		FileIOManager::FileIOManager(NLE::CONSOLE::IConsoleQueue* const console, NLE::TASK::ITaskScheduler* const taskScheduler) :
			_loadingThread(100000L),
			_console(console),
			_task(taskScheduler)
		{
			_loadingThread.setProcedure([&]() {
				FileIOOperationDesc opDesc;
				while (_fileOps.try_pop(opDesc))
				{
					if (opDesc.type == IO::WRITE)
					{
						if (write(opDesc.path, opDesc.inputData))
						{
							_task->queueProcedure([opDesc]() {
								opDesc.onSuccess(nullptr);
							}, TASK::STANDARD);
						}
						else
						{
							_task->queueProcedure([opDesc]() {
								opDesc.onFailure();
							}, TASK::STANDARD);
						}
					}
					else
					{
						std::vector<char>* data = nullptr;
						if (read(opDesc.path, data))
						{
							_task->queueProcedure([opDesc, data]() {
								opDesc.onSuccess(data);
							}, TASK::STANDARD);
						}
						else
						{
							_task->queueProcedure([opDesc]() {
								opDesc.onFailure();
							}, TASK::STANDARD);
						}
					}
				}
				_loadingThread.stop();
			}, []() {});
		}

		FileIOManager::~FileIOManager()
		{
		}

		void FileIOManager::readAsync(
			std::wstring path,
			std::function<void(std::vector<char>* data)> onSuccess,
			std::function<void()> onFailure)
		{
			FileIOOperationDesc desc;
			desc.type = READ;
			desc.path = path;
			desc.onSuccess = onSuccess;
			desc.onFailure = onFailure;

			_fileOps.push(desc);
			_loadingThread.start();
		}

		void FileIOManager::writeAsync(
			std::wstring path,
			std::vector<char>* inputData,
			std::function<void()> onSuccess,
			std::function<void()> onFailure)
		{
			FileIOOperationDesc desc;
			desc.type = WRITE;
			desc.path = path;
			desc.inputData = inputData;
			desc.onSuccess = [onSuccess](std::vector<char>* data) { onSuccess(); };
			desc.onFailure = onFailure;

			_fileOps.push(desc);
			_loadingThread.start();
		}

		bool FileIOManager::read(std::wstring path, std::vector<char>*& data)
		{
			std::ifstream file(path, std::ios::binary | std::ios::ate);
			if (!file.is_open())
			{
				_console->push(CONSOLE::ERR, L"Could not open file: " + path);
				return false;
			}

			std::vector<char>* fileData = new std::vector<char>(file.tellg());
			file.seekg(0, std::ios::beg);

			if (!file.read(&(*fileData)[0], fileData->size()))
			{
				file.close();
				delete fileData;
				_console->push(CONSOLE::ERR, L"Could not read file: " + path);
				return false;
			}

			file.close();
			data = fileData;
			return true;
		}


		bool FileIOManager::write(std::wstring path, std::vector<char>* data)
		{
			std::ofstream file(path, std::ios::binary);
			if (!file.is_open())
			{
				_console->push(CONSOLE::ERR, L"Could not open file: " + path);
				return false;
			}

			if (!file.write(&(*data)[0], data->size()))
			{
				_console->push(CONSOLE::ERR, L"Could not write to file: " + path);
				file.close();
				return false;
			}

			file.close();
			return true;
		}

		std::wstring FileIOManager::getFileExtension(std::wstring path)
		{
			return path.substr(path.find_last_of('.') + 1);
		}
	}

}