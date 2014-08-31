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
#include "RenderingEngine\SceneManager\NLRESceneManager.h"
#include "RenderingEngine\ResourceLoader\NLRETextureLoader.h"
#include "RenderingEngine\RenderingDevice\NLREDeviceController.h"
#include "RenderingEngine\RenderingDevice\NLRERenderingDevice.h"
#include "RenderingEngine\SceneManager\NLRECamera.h"


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

	_activeCamera.reset(new NLRECamera(0.0f, 40.0f, -100.0f, width, height));
}

NLRESceneManager::~NLRESceneManager()
{
	_assets.clear();
}

void NLRESceneManager::addAssets(std::vector<std::shared_ptr<NLRE_RenderableAsset>>& assets)
{
	for (std::vector<std::shared_ptr<NLRE_RenderableAsset>>::iterator it = assets.begin(); it != assets.end(); ++it)
	{
		_assets.push_back(*it);
	}
}

void NLRESceneManager::clearAssets()
{
	_assets.clear();
}

void NLRESceneManager::render()
{
	if (!_assets.empty())
	{
		for (std::vector<std::shared_ptr<NLRE_RenderableAsset>>::iterator it = _assets.begin(); it != _assets.end(); ++it)
		{
			std::shared_ptr<NLRE_RenderableAsset> asset = *it;
			NLE_MATRIX objWorld = NLEMath::NLELoadFloat4x4(&(asset->transformStruct.transformation));
			//objWorld = NLEMath::NLEMatrixTranspose(objWorld);
			//printFloat4x4(asset->transformStruct.transformation);

			NLE_MATRIX WVP = objWorld * _activeCamera->getViewProjection();
			NLRE_Transformation objTransform;
			NLEMath::NLEStoreFloat4x4(&(objTransform.transformation), NLEMath::NLEMatrixTranspose(WVP));


			_renderingDevice->updateBuffer(asset->transformationBuffer, &objTransform, sizeof(objTransform));
		}
		_deviceController->render(_assets);
	}
}

void NLRESceneManager::printFloat4x4(NLE_FLOAT4X4& matrix)
{
	NLRE_Log::console("%f %f %f %f", matrix._11, matrix._12, matrix._13, matrix._14);
	NLRE_Log::console("%f %f %f %f", matrix._21, matrix._22, matrix._23, matrix._24);
	NLRE_Log::console("%f %f %f %f", matrix._31, matrix._32, matrix._33, matrix._34);
	NLRE_Log::console("%f %f %f %f\n\n", matrix._41, matrix._42, matrix._43, matrix._44);
}

void NLRESceneManager::cameraReset()
{
	if (_activeCamera) _activeCamera->reset();
}

void NLRESceneManager::cameraUpdate()
{
	if (_activeCamera) _activeCamera->update();
}

void NLRESceneManager::cameraRotate(float yaw, float pitch)
{
	if (_activeCamera) _activeCamera->rotate(yaw, pitch);
}

void NLRESceneManager::cameraPitchUp()
{
	if (_activeCamera) _activeCamera->pitchUp();
}

void NLRESceneManager::cameraPitchDown()
{
	if (_activeCamera) _activeCamera->pitchDown();
}

void NLRESceneManager::cameraYawLeft()
{
	if (_activeCamera) _activeCamera->yawLeft();
}

void NLRESceneManager::cameraYawRight()
{
	if (_activeCamera) _activeCamera->yawRight();
}

void NLRESceneManager::cameraMoveForward()
{
	if (_activeCamera) _activeCamera->moveForward();
}

void NLRESceneManager::cameraMoveBackward()
{
	if (_activeCamera) _activeCamera->moveBackward();
}

void NLRESceneManager::cameraMoveLeft()
{
	if (_activeCamera) _activeCamera->moveLeft();
}

void NLRESceneManager::cameraMoveRight()
{
	if (_activeCamera) _activeCamera->moveRight();
}

void NLRESceneManager::cameraMoveUp()
{
	if (_activeCamera) _activeCamera->moveUp();
}

void NLRESceneManager::cameraMoveDown()
{
	if (_activeCamera) _activeCamera->moveDown();
}