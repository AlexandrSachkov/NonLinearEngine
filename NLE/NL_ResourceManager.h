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
		class ResourceManager
		{
		public:
			ResourceManager();
			~ResourceManager();

			void load(std::wstring& path, std::function<void(std::vector<char>* data)> onSuccess);
			std::vector<char>* get(std::wstring path);
			void release(std::wstring& path);

		private:
			std::wstring getFileExtension(std::wstring path);
			void addResource(std::wstring path, std::vector<char>* buffer);

			tbb::concurrent_unordered_map<std::wstring, std::vector<char>*> _resources;
		};
	}
}

#endif