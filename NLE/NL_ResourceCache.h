#pragma once

#include "NL_IResourceCache.h"
#include "NL_IFileIOManager.h"
#include "NL_IConsoleQueue.h"
#include <unordered_map>
#include <queue>
#include <map>

namespace NLE
{
	namespace RESOURCE
	{
		class ResourceCache : public IResourceCache
		{
		public:
			ResourceCache(size_t maxSizeBytes, IO::IFileIOManager_EServiceSP file, CONSOLE::IConsoleQueue_EServiceSP console);
			~ResourceCache();
			std::vector<char>* load(std::string path);
			bool save(std::vector<char>* data, std::string path);

		private:
			unsigned long long newTimeStamp();
			void addToCache(std::string path, std::vector<char>* data);

			const size_t _MAX_SIZE;
			size_t _availableSize;
			IO::IFileIOManager_EServiceSP _file;
			CONSOLE::IConsoleQueue_EServiceSP _console;

			std::unordered_map<std::string, std::pair<std::vector<char>*, unsigned long long>> _cache;
			std::map<unsigned long long, std::string> _timeStamps;
		};
	}
}