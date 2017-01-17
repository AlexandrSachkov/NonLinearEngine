#pragma once


#include <string>


namespace NLE
{
	namespace LOADER
	{
		class TextureLoader
		{
		public:
			static bool TextureLoader::loadTexture(std::string path, void* texture);
		};		
	}
}