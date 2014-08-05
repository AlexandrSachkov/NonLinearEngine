/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 Alexandr Sachkov & NonLinear Engine Team

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

#include "RenderingEngine\RenderingDevice\NLRERenderingDevice.h"
#include "RenderingEngine\ResourceLoader\NLREDirectXTexTextureLoader.h"
#include "RenderingEngine\ResourceLoader\DDSTextureLoader.h"
#include "RenderingEngine\ResourceLoader\WICTextureLoader.h"

NLREDirectXTexTextureLoader::NLREDirectXTexTextureLoader(std::shared_ptr<NLRERenderingDevice> renderingDevice)
{
	_renderingDevice = renderingDevice;

	if (!initialize())
	{
		NLRE_Log::err(NLRE_Log::CRITICAL, "NLRE Texture Loader failed to initialize");
		throw std::exception("NLRE Texture Loader failed to initialize");
	}
}

NLREDirectXTexTextureLoader::NLREDirectXTexTextureLoader(const NLREDirectXTexTextureLoader& other)
{
}

NLREDirectXTexTextureLoader::~NLREDirectXTexTextureLoader()
{

}

bool NLREDirectXTexTextureLoader::initialize()
{
	if (!_renderingDevice)
	{
		NLRE_Log::err(NLRE_Log::CRITICAL, "Rendering Device is not initialized");
		return false;
	}
	return true;
}

bool NLREDirectXTexTextureLoader::loadTexture(std::wstring path, NLRE_BIND_FLAG bindFlag, NLRE_USAGE usage, NLRE_APITexture2D*& texture2D, NLRE_APIShaderResourceView*& resourceView)
{
	HRESULT hr;
	fs::path boostPath(path.c_str());
	fs::path fileExt = boostPath.extension();

	if (fileExt == L".dds" || fileExt == L".DDS") {

		hr = DirectX::CreateDDSTextureFromFileEx(
		_renderingDevice->getAPIDevice(),
		path.c_str(),
		NULL,
		(D3D11_USAGE)usage,
		bindFlag,
		NULL,
		NULL,
		false,
		(ID3D11Resource**)&texture2D,
		(ID3D11ShaderResourceView**)&resourceView);
	}
	else {
		hr = DirectX::CreateWICTextureFromFileEx(_renderingDevice->getAPIDevice(),
		path.c_str(),
		NULL,
		(D3D11_USAGE)usage,
		bindFlag,
		NULL,
		NULL,
		false,
		(ID3D11Resource**)&texture2D,
		(ID3D11ShaderResourceView**)&resourceView);
	}
	
	if (FAILED(hr))
	{
		std::string strPath(path.begin(), path.end());
		NLRE_Log::err(NLRE_Log::REG, "Texture \"%s\" failed to load",strPath.c_str());
		return false;
	}
	return true;
}