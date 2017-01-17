#include "NL_FileIOManager.h"

#include <fstream>
#include <iostream>
#include <vector>

namespace NLE
{
	namespace IO
	{
		FileIOManager::FileIOManager(CONSOLE::IConsoleQueueSP console) :
			_console(console)
		{
		}

		FileIOManager::~FileIOManager()
		{
		}

		std::vector<char>* FileIOManager::read(std::string path)
		{
			std::ifstream file(path, std::ios::binary | std::ios::ate);
			if (!file.is_open())
			{
				_console->push(CONSOLE::ERR, "Could not open file: " + path);
				return nullptr;
			}

			std::vector<char>* fileData = new std::vector<char>(file.tellg());
			file.seekg(0, std::ios::beg);

			if (!file.read(&(*fileData)[0], fileData->size()))
			{
				file.close();
				delete fileData;
				_console->push(CONSOLE::ERR, "Could not read file: " + path);
				return nullptr;
			}

			file.close();
			return fileData;
		}


		bool FileIOManager::write(std::string path, std::vector<char>* data)
		{
			std::ofstream file(path, std::ios::binary);
			if (!file.is_open())
			{
				_console->push(CONSOLE::ERR, "Could not open file: " + path);
				return false;
			}

			if (!file.write(&(*data)[0], data->size()))
			{
				_console->push(CONSOLE::ERR, "Could not write to file: " + path);
				file.close();
				return false;
			}

			file.close();
			return true;
		}
	}

}