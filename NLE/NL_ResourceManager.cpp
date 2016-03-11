#include "NL_ResourceManager.h"

#include "NL_FileIOManager.h"

namespace NLE
{
	namespace RESOURCE
	{
		ResourceManager::ResourceManager(NLE::IO::FileIOManager& fileIO) :
			_file(fileIO)
		{
		}

		ResourceManager::~ResourceManager()
		{
		}

		void ResourceManager::load(std::wstring& path, std::function<void(std::vector<char>* data)> onSuccess)
		{

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