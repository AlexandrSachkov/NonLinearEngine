#ifndef NL_RESOURCE_MANAGER_H_
#define NL_RESOURCE_MANAGER_H_

#include "NL_Thread.h"

#include "tbb/atomic.h"
#include "tbb/concurrent_unordered_map.h"
#include "tbb/concurrent_queue.h"

#include <string>
#include <vector>


namespace NLE
{
	namespace RESOURCE
	{
		struct NleFileHeader
		{
			NleFileHeader()
			{
				memset(_identifier, 0, 36);
				_version = 1.0f;
				_originalSize = 0;
			}

			NleFileHeader(std::string identifier, float version, size_t originalSize) :
				_version(version),
				_originalSize(originalSize)
			{
				memset(_identifier, 0, 36);
				strncpy(_identifier, identifier.c_str(), 36);
			}

			char _identifier[36];
			float _version;
			size_t _originalSize;
		};

		class ResourceManager
		{
		public:
			ResourceManager();
			~ResourceManager();

			void load(std::wstring& path, tbb::atomic<bool>& ready);
			std::vector<char>* get(std::wstring path);
			void release(std::wstring& path);

		private:
			std::wstring getFileExtension(std::wstring path);
			void addResource(std::wstring path, std::vector<char>* buffer);

			Core::Thread _loadingThread;

			tbb::concurrent_unordered_map<std::wstring, std::vector<char>*> _resources;
			tbb::concurrent_queue<std::pair<std::wstring, tbb::atomic<bool>*>> _toLoad;
		};
	}
}

#endif