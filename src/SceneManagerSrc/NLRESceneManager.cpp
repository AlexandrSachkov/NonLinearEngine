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
#include "SceneManager\NLRESceneManager.h"


NLRESceneManager::NLRESceneManager(
	std::shared_ptr<NLREDeviceController> deviceController, 
	std::shared_ptr<NLRERenderingDevice> renderingDevice,
	std::shared_ptr<NLRETextureLoader> textureLoader,
	int width, 
	int height)
{
	if (!deviceController || !renderingDevice || !textureLoader)
	{
		throw std::exception("Container failed to initialize: NULL ptr");
	}
	_deviceController = deviceController;
	_renderingDevice = renderingDevice;
	_textureLoader = textureLoader;

	_mainCamera = new NLRECamera(0.0f, 40.0f, -100.0f, width, height);
}

NLRESceneManager::~NLRESceneManager()
{

}

void NLRESceneManager::addAssets(std::vector<std::shared_ptr<NLRE_RenderableAsset>>& assets)
{
	for (std::vector<std::shared_ptr<NLRE_RenderableAsset>>::iterator it = assets.begin(); it != assets.end(); ++it)
	{
		_assets.push_back(*it);
	}
}

void NLRESceneManager::render()
{
	for (std::vector<std::shared_ptr<NLRE_RenderableAsset>>::iterator it = _assets.begin(); it != _assets.end(); ++it)
	{
		std::shared_ptr<NLRE_RenderableAsset> asset = *it;
		NLE_MATRIX objWorld = NLEMath::NLELoadFloat4x4(&(asset->transformStruct.transformation));

		NLE_MATRIX WVP = objWorld * _mainCamera->getViewProjection();
		NLRE_Transformation objTransform;
		NLEMath::NLEStoreFloat4x4(&(objTransform.transformation), NLEMath::NLEMatrixTranspose(WVP));

		_renderingDevice->updateBuffer(asset->transformationBuffer, &objTransform, sizeof(objTransform));
	}
	_deviceController->render(_assets);
}