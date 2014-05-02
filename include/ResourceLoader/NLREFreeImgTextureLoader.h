#ifndef FREE_IMG_TEXTURE_LOADER_
#define FREE_IMG_TEXTURE_LOADER_

#include "NLRETextureLoader.h"
#include "FreeImage\include\FreeImage.h"
#include "RenderingDevice\NLRERenderingDevice.h"

class NLREFreeImgTextureLoader : public virtual NLRETextureLoader
{
public:
	NLREFreeImgTextureLoader(NLRERenderingDevice* renderingDevice);
	NLREFreeImgTextureLoader(const NLREFreeImgTextureLoader& other);
	~NLREFreeImgTextureLoader();

	static void freeImgErrorCallback(FREE_IMAGE_FORMAT format, const char* message);
	bool loadTexture2D(std::wstring path, NLRE_APITexture2D*& texture2D, NLRE_APIShaderResourceView*& resourceView);
private:
	bool initialize();

	NLRERenderingDevice* _renderingDevice;
};

#endif