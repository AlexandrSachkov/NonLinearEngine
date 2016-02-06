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
	namespace IO
	{
		FileIOManager* FileIOManager::_ioManager = nullptr;

		FileIOManager::FileIOManager() :
			_loadingThread(100000L)
		{
			_loadingThread.setProcedure([&]() {
				FileIOOperationDesc opDesc;
				while (_fileOps.try_pop(opDesc))
				{
					if (opDesc.opType == IO::WRITE)
					{
						writeFile(opDesc.path, opDesc.compressed, opDesc.inputData, opDesc.onSuccess, opDesc.onFailure);
					}
					else
					{
						readFile(opDesc.path, opDesc.onSuccess, opDesc.onFailure);
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

		void FileIOManager::read(
			std::wstring path, 
			std::function<void(std::vector<char>* data)> onSuccess, 
			std::function<void()> onFailure)
		{
			FileIOOperationDesc desc(path, IO::READ, false, nullptr, onSuccess, onFailure);
			fileOperation(desc);
		}

		void FileIOManager::write(
			std::wstring path,
			bool compressed,
			std::vector<char>* inputData,
			std::function<void()> onSuccess,
			std::function<void()> onFailure)
		{
			FileIOOperationDesc desc(path, IO::WRITE, compressed, inputData, [onSuccess](std::vector<char>* data) {
				onSuccess();
			}, onFailure);
			fileOperation(desc);
		}

		void FileIOManager::readFile(std::wstring& path, std::function<void(std::vector<char>* data)> onSuccess, std::function<void()> onFailure)
		{
			std::ifstream file(path, std::ios::binary | std::ios::ate);
			if (file.is_open())
			{
				std::vector<char>* fileData = new std::vector<char>(file.tellg());
				file.seekg(0, std::ios::beg);

				if (file.read(&(*fileData)[0], fileData->size()))
				{
					Core::DeviceCore::instance().runAsync([this, path, fileData, onSuccess, onFailure]() {
						std::wstring myPath(path);
						auto* decompressed = decompressIfNeeded(myPath, fileData);
						if (decompressed)
						{
							onSuccess(decompressed);
						}
						else
						{
							onFailure();
						}
					}, Core::Priority::STANDARD);
				}
				else
				{
					delete fileData;
					CONSOLE::out(CONSOLE::ERR, L"Could not read file: " + path);
					Core::DeviceCore::instance().runAsync([onFailure]() {
						onFailure();
					}, Core::Priority::STANDARD);
				}
				file.close();
			}
			else
			{
				CONSOLE::out(CONSOLE::ERR, L"Could not open file: " + path);
				Core::DeviceCore::instance().runAsync([onFailure]() {
					onFailure();
				}, Core::Priority::STANDARD);
			}
		}


		void FileIOManager::writeFile(std::wstring path, bool compress, std::vector<char>* data, std::function<void(std::vector<char>* data)> onSuccess, std::function<void()> onFailure)
		{
			auto* compressed = compressIfNeeded(path, compress, data);
			if (!compressed)
			{
				Core::DeviceCore::instance().runAsync([onFailure]() {
					onFailure();
				}, Core::Priority::STANDARD);
				return;
			}
				

			std::ofstream file(path, std::ios::binary);
			if (file.is_open())
			{
				if (file.write(&(*compressed)[0], compressed->size()))
				{
					Core::DeviceCore::instance().runAsync([&]() {
						onSuccess(data);
					}, Core::Priority::STANDARD);
				}
				else
				{
					CONSOLE::out(CONSOLE::ERR, L"Could not write to file: " + path);
					Core::DeviceCore::instance().runAsync([onFailure]() {
						onFailure();
					}, Core::Priority::STANDARD);
				}
				file.close();
			}
			else
			{
				CONSOLE::out(CONSOLE::ERR, L"Could not open file: " + path);
				Core::DeviceCore::instance().runAsync([onFailure]() {
					onFailure();
				}, Core::Priority::STANDARD);
			}
			if (compressed != data)
			{
				delete compressed;
			}		
		}

		std::wstring FileIOManager::getFileExtension(std::wstring path)
		{
			return path.substr(path.find_last_of('.') + 1);
		}

		std::vector<char>* FileIOManager::compressIfNeeded(std::wstring& path, bool compress, std::vector<char>* buffer)
		{
			if (isEngineType(path))
			{
				TLS::StringConverter::reference converter = TLS::strConverter.local();
				NleFileHeader header(converter.to_bytes(getFileExtension(path)), 1.0f, buffer->size(), compress);

				std::vector<char>* outBuffer = new std::vector<char>(sizeof(header));
				memcpy(&(*outBuffer)[0], &header, sizeof(header));	

				if (compress)
				{
					std::vector<char>* compressed = nullptr;
					if (DataCompressionManager::compress(buffer, compressed))
					{
						outBuffer->insert(outBuffer->end(), compressed->begin(), compressed->end());
						delete compressed;
						return outBuffer;
					}
					else
					{
						delete outBuffer;
						return nullptr;
					}
				}
				else
				{
					outBuffer->insert(outBuffer->end(), buffer->begin(), buffer->end());
					return outBuffer;
				}
			}
			else
			{
				return buffer;
			}
		}

		std::vector<char>* FileIOManager::decompressIfNeeded(std::wstring& path, std::vector<char>* buffer)
		{
			if (isEngineType(path))
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

				if (!header._compressed)
				{
					return buffer;
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

		bool FileIOManager::isEngineType(const std::wstring& path)
		{
			if (getFileExtension(path).find(L"nle") != std::string::npos)
				return true;
			return false;
		}
	}
	
}