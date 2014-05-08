/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 NonLinear Rendering Engine Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

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

bool NLREFreeImgTextureLoader::loadTexture2D(std::wstring path, NLRE_BIND_FLAG bindFlag, NLRE_USAGE usage, NLRE_APITexture2D*& texture2D, NLRE_APIShaderResourceView*& resourceView)
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