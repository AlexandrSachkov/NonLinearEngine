#include "NL_ResourceManager.h"

#include "NL_FileIOManager.h"
#include "NL_DataCompressionManager.h"
#include "NL_Console.h"

namespace NLE
{
	namespace RESOURCE
	{
		ResourceManager::ResourceManager() :
			_loadingThread(100000L)
		{
			_loadingThread.setProcedure([&]() {
				std::pair<std::wstring, tbb::atomic<bool>*> loadingDesc;
				while (_toLoad.try_pop(loadingDesc))
				{
					std::vector<char>* buffer = nullptr;
					if (FileIOManager::readFile(loadingDesc.first, buffer))
					{
						if (getFileExtension(loadingDesc.first).find(L"nle"))
						{
							NleFileHeader header;
							std::copy(&header, &header + sizeof(header), reinterpret_cast<NleFileHeader*>(&(*buffer)[0]));
							buffer->erase(buffer->begin(), buffer->begin() + sizeof(header));

							if (header._originalSize > 0) //data is compressed
							{
								std::vector<char>* decompressed = new std::vector<char>(header._originalSize);
								if (DataCompressionManager::decompress(buffer, decompressed))
								{
									addResource(loadingDesc.first, decompressed);								
									loadingDesc.second->store(true);
								}
								else
								{
									delete decompressed;								
								}
								delete buffer;
							}
							else
							{
								addResource(loadingDesc.first, buffer);
								loadingDesc.second->store(true);
							}
						}
						else
						{
							addResource(loadingDesc.first, buffer);
							loadingDesc.second->store(true);
						}
					}
					else
					{
						CONSOLE::out(CONSOLE::ERR, L"Failed to load resource: " + loadingDesc.first);
					}
				}
				_loadingThread.stop();
			}, []() {});
		}

		ResourceManager::~ResourceManager()
		{
		}

		void ResourceManager::load(std::wstring& path, tbb::atomic<bool>& ready)
		{
			_toLoad.push({path, &ready});
			_loadingThread.start();
		}

		std::vector<char>* ResourceManager::get(std::wstring path)
		{
			auto iter = _resources.find(path);
			if (iter != _resources.end())
			{
				return iter->second;
			}
			return nullptr;
		}

		void ResourceManager::release(std::wstring& path)
		{
			auto iter = _resources.find(path);
			if (iter != _resources.end())
			{
				delete iter->second;
				iter->second = nullptr;
			}
		}

		std::wstring ResourceManager::getFileExtension(std::wstring path)
		{
			return path.substr(path.find_last_of('.') + 1);
		}

		void ResourceManager::addResource(std::wstring path, std::vector<char>* buffer)
		{
			auto iter = _resources.find(path);
			if (iter != _resources.end())
			{
				iter->second = buffer;
			}
			else
			{
				_resources.insert(std::make_pair<>(path, buffer));
			}
		}
	}
}