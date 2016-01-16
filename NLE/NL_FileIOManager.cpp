#include "NL_FileIOManager.h"

#include "NL_Console.h"

#include <fstream>
#include <iostream>
#include <vector>

namespace NLE
{
	bool FileIOManager::readFile(std::wstring path, std::vector<char>*& data)
	{
		std::ifstream file(path, std::ios::binary | std::ios::ate);
		if (file.is_open())
		{
			std::vector<char>* fileData = new std::vector<char>(file.tellg());
			file.seekg(0, std::ios::beg);

			if (file.read(&(*fileData)[0], fileData->size()))
			{
				data = fileData;
				file.close();
			}
			else
			{
				delete fileData;
				file.close();
				CONSOLE::out(CONSOLE::ERR, L"Could not read file: " + path);
				return false;
			}
		}
		else
		{
			CONSOLE::out(CONSOLE::ERR, L"Could not open file: " + path);
			return false;
		}

		return true;
	}


	bool FileIOManager::writeFile(std::wstring path, const std::vector<char>* data)
	{
		std::ofstream file(path, std::ios::binary);
		if (file.is_open())
		{
			if (!file.write(&(*data)[0], data->size()))
			{
				file.close();
				CONSOLE::out(CONSOLE::ERR, L"Could not write to file: " + path);
				return false;
			}
		}
		else
		{
			CONSOLE::out(CONSOLE::ERR, L"Could not open file: " + path);
			return false;
		}

		return true;
	}
}