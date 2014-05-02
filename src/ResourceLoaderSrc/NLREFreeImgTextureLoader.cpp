#include "stdafx.h"
#include "ResourceLoader\NLREFreeImgTextureLoader.h"

NLREFreeImgTextureLoader::NLREFreeImgTextureLoader(NLRERenderingDevice* renderingDevice)
{
	_renderingDevice = renderingDevice;
	if (!initialize())
	{
		NLRE_Log::err(NLRE_Log::CRITICAL, "Free Image Texture Loader failed to initialize");
		throw std::exception("Free Image Texture Loader failed to initialize");
	}
}

bool NLREFreeImgTextureLoader::initialize()
{
	if (_renderingDevice == NULL) return false;
	FreeImage_Initialise(true);
	FreeImage_SetOutputMessage(freeImgErrorCallback);

	return true;
}

NLREFreeImgTextureLoader::NLREFreeImgTextureLoader(const NLREFreeImgTextureLoader& other)
{
}

NLREFreeImgTextureLoader::~NLREFreeImgTextureLoader()
{
	FreeImage_DeInitialise();

}

void NLREFreeImgTextureLoader::freeImgErrorCallback(FREE_IMAGE_FORMAT fif, const char* message)
{
	const char* format = FreeImage_GetFormatFromFIF(fif);
	NLRE_Log::err(NLRE_Log::REG, "Texture Loader Error -> FORMAT: ", format == NULL ? "NULL" : format,", MESSAGE: ",message);
}

bool NLREFreeImgTextureLoader::loadTexture2D(std::wstring path, NLRE_USAGE usage, NLRE_BIND_FLAG bindFlag, NLRE_APITexture2D*& texture2D, NLRE_APIShaderResourceView*& resourceView)
{
	std::string filePath(path.begin(),path.end());
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filePath.c_str(), 0);
	if (format == FIF_UNKNOWN) format = FreeImage_GetFIFFromFilename(filePath.c_str());
	if (format == FIF_UNKNOWN) return false;

	FIBITMAP* bitmap = FreeImage_Load(format, filePath.c_str(), 0);
	FIBITMAP* bitmap2 = FreeImage_ConvertTo32Bits(bitmap);
	FreeImage_Unload(bitmap);

	unsigned int pitch = FreeImage_GetPitch(bitmap2);
	unsigned int width = FreeImage_GetWidth(bitmap2);
	unsigned int height = FreeImage_GetHeight(bitmap2);

	std::vector<char> out(FreeImage_GetWidth(bitmap2) * FreeImage_GetHeight(bitmap2) * 4);
	FreeImage_ConvertToRawBits((unsigned char*)out.data(), bitmap2, FreeImage_GetWidth(bitmap2) * 4, 32, FI_RGBA_BLUE_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_RED_MASK, true);

	bool status = false;
	status = _renderingDevice->createTexture2D(
		width, 
		height, 
		false, 
		1, 
		usage,
		bindFlag,
		&out[0], 
		pitch, 
		texture2D);

	
	FreeImage_Unload(bitmap2);
	if (!status) return false;

	status = _renderingDevice->createShaderResourceViewFromTexture2D(texture2D, resourceView);
	if (!status) return false;
	
	return true;
}