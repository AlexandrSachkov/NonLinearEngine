#ifndef NL_TEXTURE_LOADER_H_
#define NL_TEXTURE_LOADER_H_


#include <string>


namespace NLE
{
	namespace LOADER
	{
		class TextureLoader
		{
		public:
			static bool TextureLoader::loadTexture(std::wstring path, void* texture);
		};		
	}
}

#endif