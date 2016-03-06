#include "NL_ResourceManager.h"

#include "NL_FileIOManager.h"
#include "NL_DataCompressionManager.h"

namespace NLE
{
	namespace RESOURCE
	{
		ResourceManager::ResourceManager()
		{
		}

		ResourceManager::~ResourceManager()
		{
		}

		void ResourceManager::load(std::wstring& path, std::function<void(std::vector<char>* data)> onSuccess)
		{
			/*FileIOOperationDesc desc (
				path, 
				false, 
				nullptr, 
				[&](std::vector<char>* data) {
					auto* decompressed = decompressIfNeeded(path, data);
					if (decompressed)
					{
						onSuccess(decompressed);
					}
				});

			FileIOManager::instance().fileOperation(desc);*/
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