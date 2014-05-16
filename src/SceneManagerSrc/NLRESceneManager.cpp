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


NLRESceneManager::NLRESceneManager(NLREDeviceController* deviceController, NLRERenderingDevice* renderingDevice, NLRETextureLoader* textureLoader, int width, int height)
{
	if (!deviceController || !renderingDevice || !textureLoader)
	{
		throw std::exception("Container failed to initialize: NULL ptr");
	}
	_deviceController = deviceController;
	_renderingDevice = renderingDevice;
	_textureLoader = textureLoader;

	_mainCamera = new NLRECamera(0.0f, 4.0f, -4.0f, width, height);

	mCamView = new NLE_FLOAT4X4();
	mCamProjection = new NLE_FLOAT4X4();

	NLE_VECTOR camPosition = NLEMath::NLEVectorSet(0.0f, 4.0f, -4.0f, 0.0f);
	NLE_VECTOR camTarget = NLEMath::NLEVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	NLE_VECTOR camUp = NLEMath::NLEVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//Set the View matrix
	NLE_MATRIX camView = NLEMath::NLEMatrixLookAtLH(camPosition, camTarget, camUp);
	NLE_VECTOR rotAxis = NLEMath::NLEVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	NLE_MATRIX rotation = NLEMath::NLEMatrixRotationAxis(rotAxis, 0.0f);
	camView = camView * rotation;
	NLEMath::NLEStoreFloat4x4(mCamView, camView);
	
	//Set the Projection matrix
	NLE_MATRIX camProjection = NLEMath::NLEMatrixPerspectiveFovLH(0.5f*3.14f, (float)width / height, 1.0f, 1000.0f);
	NLEMath::NLEStoreFloat4x4(mCamProjection, camProjection);

	
	//XMVECTOR rotAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//XMMATRIX rotation = XMMatrixRotationAxis(rotAxis, rot);
	//NLE_MATRIX translation = NLEMath::NLEMatrixTranslation(0.0f, 0.0f, 4.0f);
	//NLE_MATRIX scale = NLEMath::NLEMatrixScaling(1.3f, 1.3f, 1.3f);

}

NLRESceneManager::~NLRESceneManager()
{
	delete mCamView;
	delete mCamProjection;

	for (std::vector<NLRE_RenderableAsset*>::iterator it = _assets.begin(); it != _assets.end(); ++it)
	{
		delete (NLRE_RenderableAsset*)(*it);
	}
}

void NLRESceneManager::addAssets(std::vector<NLRE_RenderableAsset*>& assets)
{
	for (std::vector<NLRE_RenderableAsset*>::iterator it = assets.begin(); it != assets.end(); ++it)
	{
		_assets.push_back(*it);
	}
}

void NLRESceneManager::render()
{
	NLE_MATRIX camView = NLEMath::NLELoadFloat4x4(mCamView);
	NLE_MATRIX camProjection = NLEMath::NLELoadFloat4x4(mCamProjection);

	for (std::vector<NLRE_RenderableAsset*>::iterator it = _assets.begin(); it != _assets.end(); ++it)
	{
		NLRE_RenderableAsset* asset = (NLRE_RenderableAsset*)(*it);
		NLE_MATRIX objWorld = NLEMath::NLELoadFloat4x4(&(asset->transformStruct.transformation));

		NLE_MATRIX WVP = objWorld * camView * camProjection;
		NLRE_Transformation objTransform;
		NLEMath::NLEStoreFloat4x4(&(objTransform.transformation), NLEMath::NLEMatrixTranspose(WVP));

		_renderingDevice->updateBuffer(asset->transformationBuffer, &objTransform, sizeof(objTransform));
	}
	_deviceController->render(_assets);
}