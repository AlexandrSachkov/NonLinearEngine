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
#pragma once

#ifndef NLRE_
#define NLRE_

#include "RenderingDevice\NLRERenderingDevice.h"
class NLREAssetImporter;
class NLRESceneManager;
class NLREDeviceController;
class NLRETextureLoader;

class NLRE
{
public:
	NLRE(NLEWindowReference hwndVal, int widthVal, int heightVal);
	~NLRE();

	void render();
	void importAsset(std::wstring path);

	std::shared_ptr<NLREAssetImporter> getAssetImporter();
	std::shared_ptr<NLRESceneManager> getSceneManager();
	std::shared_ptr<NLREDeviceController> getDeviceController();
	std::shared_ptr<NLRETextureLoader> getTextureLoader();

private:
	std::shared_ptr<NLREAssetImporter> _assetImporter;
	std::shared_ptr<NLREDeviceController> _deviceController;
	std::shared_ptr<NLRESceneManager> _sceneManager;
	std::shared_ptr<NLRETextureLoader> _textureLoader;
	
};
#endif