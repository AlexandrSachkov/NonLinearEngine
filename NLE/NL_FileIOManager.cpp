#include "NL_FileIOManager.h"

#include "NL_DeviceCore.h"
#include "NL_Console.h"
#include "NL_DataCompressionManager.h"
#include "NL_ThreadLocal.h"

#include <fstream>
#include <iostream>
#include <vector>

namespace NLE
{
	FileIOManager* FileIOManager::_ioManager = nullptr;

	FileIOManager::FileIOManager() :
		_loadingThread(100000L)
	{
		_loadingThread.setProcedure([&]() {
			FileIOOperationDesc opDesc;
			while (_fileOps.try_pop(opDesc))
			{
				if (opDesc.write)
				{
					writeFile(opDesc.path, opDesc.inputData, opDesc.onSuccess);
				}
				else
				{
					readFile(opDesc.path, opDesc.onSuccess);
				}
			}
			_loadingThread.stop();
		}, []() {});
	}

	FileIOManager::~FileIOManager()
	{
	}

	void FileIOManager::fileOperation(FileIOOperationDesc& opDesc)
	{
		_fileOps.push(opDesc);
		_loadingThread.start();
	}

	void FileIOManager::readFile(std::wstring& path, std::function<void(std::vector<char>* data)> onSuccess)
	{
		std::ifstream file(path, std::ios::binary | std::ios::ate);
		if (file.is_open())
		{
			std::vector<char>* fileData = new std::vector<char>(file.tellg());
			file.seekg(0, std::ios::beg);

			if (file.read(&(*fileData)[0], fileData->size()))
			{
				Core::DeviceCore::instance().runAsync([this, path, fileData, onSuccess]() {
					std::wstring myPath(path);
					auto* decompressed = decompressIfNeeded(myPath, fileData);
					if (decompressed)
					{
						onSuccess(decompressed);
					}					
				}, Core::Priority::STANDARD);
			}
			else
			{
				delete fileData;
				CONSOLE::out(CONSOLE::ERR, L"Could not read file: " + path);
			}
			file.close();
		}
		else
		{
			CONSOLE::out(CONSOLE::ERR, L"Could not open file: " + path);
		}
	}


	void FileIOManager::writeFile(std::wstring path, std::vector<char>* data, std::function<void(std::vector<char>* data)> onSuccess)
	{
		auto* compressed = compressIfNeeded(path, data);
		if(!compressed)
			return;

		std::ofstream file(path, std::ios::binary);
		if (file.is_open())
		{	
			if (file.write(&(*compressed)[0], compressed->size()))
			{
				Core::DeviceCore::instance().runAsync([&]() {
					onSuccess(compressed);
				}, Core::Priority::STANDARD);
			}
			else
			{
				CONSOLE::out(CONSOLE::ERR, L"Could not write to file: " + path);
			}
			file.close();
		}
		else
		{
			CONSOLE::out(CONSOLE::ERR, L"Could not open file: " + path);
		}
	}

	std::wstring FileIOManager::getFileExtension(std::wstring path)
	{
		return path.substr(path.find_last_of('.') + 1);
	}

	std::vector<char>* FileIOManager::compressIfNeeded(std::wstring& path, std::vector<char>* buffer)
	{
		if (isCompressedType(path))
		{
			TLS::StringConverter::reference converter = TLS::strConverter.local();
			NleFileHeader header(converter.to_bytes(getFileExtension(path)), 1.0f, buffer->size());

			std::vector<char>* outBuffer = new std::vector<char>(sizeof(header));
			memcpy(&(*outBuffer)[0], &header, sizeof(header));

			std::vector<char>* compressed = nullptr;
			if (DataCompressionManager::compress(buffer, compressed))
			{
				outBuffer->insert(outBuffer->end(), compressed->begin(), compressed->end());
				delete buffer;
				delete compressed;
				return outBuffer;
			}
			else
			{
				delete buffer;
				delete outBuffer;
				return nullptr;
			}
		}
		else
		{
			return buffer;
		}
	}

	std::vector<char>* FileIOManager::decompressIfNeeded(std::wstring& path, std::vector<char>* buffer)
	{
		if (isCompressedType(path))
		{		
			NleFileHeader header;
			memcpy(&header, &(*buffer)[0], sizeof(header));
			buffer->erase(buffer->begin(), buffer->begin() + sizeof(header));

			TLS::StringConverter::reference converter = TLS::strConverter.local();
			auto identifier = converter.from_bytes(header._identifier);
			if (getFileExtension(path).compare(identifier) != 0)
			{
				CONSOLE::out(CONSOLE::ERR, L"Resource identifier " + identifier + L" and file extension " + getFileExtension(path) + L" are mismatched");
				delete buffer;
				return nullptr;
			}

			std::vector<char>* decompressed = new std::vector<char>(header._originalSize);
			if (DataCompressionManager::decompress(buffer, decompressed))
			{
				delete buffer;
				return decompressed;
			}
			else
			{
				delete buffer;
				delete decompressed;
				return nullptr;
			}
		}
		else
		{
			return buffer;
		}
	}

	bool FileIOManager::isCompressedType(const std::wstring& path)
	{
		if (getFileExtension(path).find(L"nle") != std::string::npos)
			return true;
		return false;
	}
}