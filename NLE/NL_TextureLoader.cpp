#include "NL_TextureLoader.h"

#include "NL_ThreadLocal.h"

#include <cstdio>
#include <cstdlib>


namespace NLE
{
	namespace LOADER
	{
		bool TextureLoader::loadTexture(std::string path, void* texture)
		{
			/*TLS::StringConverter::reference converter = TLS::strConverter.local();

			FILE* file = nullptr;
			errno_t err = fopen_s(&file, converter.to_bytes(path).c_str(), "rb");
			if (err != 0)
			{
				CONSOLE::out(CONSOLE::ERR, L"Texture at " + path + L": could not open file");
				return false;
			}

			fseek(file, 0, SEEK_END);
			size_t fileSize = ftell(file);
			unsigned char* fileData = new unsigned char[fileSize];
			memset(fileData, 0, fileSize);
			fread(fileData, 1, fileSize, file);
			fclose(file);


			GLuint tex = 0;
			GLenum target;
			GLenum glerror;
			GLboolean isMipmapped;
			KTX_error_code ktxerror;

			ktxerror = ktxLoadTextureM(fileData, (GLsizei)fileSize, &tex, &target, NULL, &isMipmapped, &glerror,
				0, NULL);
				*/
			return true;
		}
	}
}