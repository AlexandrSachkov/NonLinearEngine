#include "NL_ResourceCache.h"
#include <chrono>

namespace NLE
{
	namespace RESOURCE
	{
		ResourceCache::ResourceCache(
			size_t maxSizeBytes, 
			IO::IFileIOManager_EServiceSP file,
			CONSOLE::IConsoleQueue_EServiceSP console
			) :
			_MAX_SIZE(maxSizeBytes),
			_availableSize(maxSizeBytes),
			_file(file),
			_console(console)
		{
		}

		ResourceCache::~ResourceCache()
		{
		}

		std::vector<char>* ResourceCache::load(std::string path)
		{
			auto it = _cache.find(path);
			if (it != _cache.end())
			{
				//retrieve data
				auto data = it->second.first;
				auto time = it->second.second;

				//delete old entry
				_cache.erase(it);
				auto it = _timeStamps.find(time);
				if (it != _timeStamps.end())
				{
					_timeStamps.erase(it);
				}

				//add new entry
				addToCache(path, data);

				_console->push(CONSOLE::STANDARD, "Resource " + path + " is retrieved from cache");

				//copy and return data
				auto tempData = new std::vector<char>(*data);
				return tempData;
			}

			auto fileData = _file->read(path);
			if (fileData)
			{
				//add new entry
				addToCache(path, fileData);

				_console->push(CONSOLE::STANDARD, "Resource " + path + " is retrieved from file and cached");

				//copy and return data
				auto tempData = new std::vector<char>(*fileData);
				return tempData;
			}

			_console->push(CONSOLE::STANDARD, "Unable to retrieve resource: " + path);
			return nullptr;
		}

		bool ResourceCache::save(std::vector<char>* data, std::string path)
		{
			return false;
		}

		void ResourceCache::addToCache(std::string path, std::vector<char>* data)
		{
			auto time = newTimeStamp();
			_cache.insert({ path, {data, time} });
			_timeStamps.insert({ time, path });
		}

		unsigned long long ResourceCache::newTimeStamp()
		{
			auto time = std::chrono::high_resolution_clock::now();
			return time.time_since_epoch().count();
		}
	}
}