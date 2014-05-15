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
#include "NLRE.h"

NLRE::NLRE(HWND hwndVal, int widthVal, int heightVal){
	_deviceController = new NLREDeviceController(hwndVal, widthVal, heightVal, NLRE_RENDERING_TECHNIQUE_ID::NLRE_FORWARD_RT);
	_renderingDevice = _deviceController->getRenderingDevice();
	_textureLoader = new NLRETextureLoader(_renderingDevice);
	_container = new Container(_deviceController, _renderingDevice, _textureLoader, widthVal, heightVal);
	_assetImporter = new NLREAssetImporter(_renderingDevice, _textureLoader);
}

NLRE::~NLRE(){
	delete _assetImporter;
	delete _container;
	delete _textureLoader;
	delete _deviceController;
}

void NLRE::render()
{
	_container->render();
}

void NLRE::importAsset(std::wstring path)
{
	std::vector<NLRE_RenderableAsset*> assets;
	std::string strPath(path.begin(), path.end());
	if (_assetImporter->importAssets(path, assets))
	{
		NLRE_Log::console("Successfully imported asset at: %s", strPath.c_str());
		NLRE_Log::console("Number of items in the asset vector: %i", assets.size());
		_container->addAssets(assets);
	}
}
