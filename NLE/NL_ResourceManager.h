#ifndef NL_RESOURCE_MANAGER_H_
#define NL_RESOURCE_MANAGER_H_

#include "NL_IResourceManager.h"
#include "NL_FileIOManager.h"

#include "tbb/atomic.h"
#include "tbb/concurrent_unordered_map.h"
#include "tbb/concurrent_queue.h"

#include <string>
#include <vector>


namespace NLE
{
	namespace RESOURCE
	{
		class ResourceManager : public IResourceManager
		{
		public:
			ResourceManager(NLE::IO::FileIOManager& fileIO);
			~ResourceManager();

			void load(std::wstring& path, std::function<void(std::vector<char>* data)> onSuccess);
			std::vector<char>* get(std::wstring path);
			void release(std::wstring& path);

		private:
			void addResource(std::wstring path, std::vector<char>* buffer);

			NLE::IO::FileIOManager& _file;
			tbb::concurrent_unordered_map<std::wstring, std::vector<char>*> _resources;
		};
	}
}

#endif