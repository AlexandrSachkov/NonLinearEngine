#pragma once

#include <vector>
#include <string>

namespace NLE
{
	namespace RESOURCE
	{
		class IResourceCache
		{
		public:
			virtual std::vector<char>* load(std::string path) = 0;
			virtual bool save(std::vector<char>* data, std::string path) = 0;
			virtual ~IResourceCache() {}
		};
	}
}