/*
-----------------------------------------------------------------------------
This source file is part of NLE
(NonLinear Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearEngine

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
#include "RenderingEngine\NLRE.h"
#include "RenderingEngine\RenderingDevice\NLRERenderingDevice.h"
#include "RenderingEngine\SceneManager\NLRESceneManager.h"
#include "RenderingEngine\ResourceLoader\NLREAssimpAssetImporter.h"
#include "RenderingEngine\ResourceLoader\NLREDirectXTexTextureLoader.h"
#include "RenderingEngine\RenderingDevice\NLREDeviceController.h"
#include "NLETimer.h"

std::shared_ptr<NLRE> NLRE::_nlre = NULL;

//===========================================================================================================================
std::shared_ptr<NLRE> NLRE::instance(
	NLEWindowReference hwnd,
	int width,
	int height
	)
{
	if (!_nlre)
	{
		_nlre.reset(new NLRE(hwnd, width, height));
	}
	return _nlre;
}

//===========================================================================================================================
std::shared_ptr<NLRE> NLRE::instance()
{
	if (!_nlre) throw std::runtime_error("NLRE is not initialized, use the alternative instance()");
	return _nlre;
}

//===========================================================================================================================
NLRE::NLRE(
	NLEWindowReference hwnd, 
	int width, 
	int height){
	_deviceController.reset(new NLREDeviceController(hwnd, width, height, NLRE_RENDERING_TECHNIQUE_ID::NLRE_FORWARD_RT));
	std::shared_ptr<NLRERenderingDevice> renderingDevice = _deviceController->getRenderingDevice();
	_textureLoader.reset(new NLREDirectXTexTextureLoader(renderingDevice));
	_sceneManager.reset(new NLRESceneManager(_deviceController, renderingDevice, _textureLoader, width, height));
	_assetImporter.reset(new NLREAssimpAssetImporter(renderingDevice, _textureLoader));

	_fpsTimer = new NLETimer();
	NLRE_Log::console("======> NLRE successfully initialized.");
}

//===========================================================================================================================
NLRE::~NLRE()
{
	delete _fpsTimer;
}

//===========================================================================================================================
void NLRE::render()
{
	_sceneManager->cameraUpdate();
	_sceneManager->render();
}

//===========================================================================================================================
bool NLRE::importAsset(std::wstring path)
{
	NLETimer timer;
	std::vector<std::shared_ptr<NLRE_RenderableAsset>> assets;
	std::string strPath(path.begin(), path.end());
	timer.now();
	if (_assetImporter->importAssets(path, assets))
	{
		NLRE_Log::console("Successfully imported asset at: %s", strPath.c_str());
		NLRE_Log::console("Number of items in the asset vector: %i", assets.size());
		NLRE_Log::console("It took %Lf seconds to load the model.\n", timer.now());
		_sceneManager->addAssets(assets);
		return true;
	}
	return false;
}

//===========================================================================================================================
void NLRE::disposeAssets()
{
	_sceneManager->disposeAssets();
}

long double NLRE::getFPS()
{
	return 0.0;
}

//===========================================================================================================================
std::shared_ptr<NLREAssetImporter> NLRE::getAssetImporter()
{
	return _assetImporter;
}

//===========================================================================================================================
std::shared_ptr<NLRESceneManager> NLRE::getSceneManager()
{
	return _sceneManager;
}

//===========================================================================================================================
std::shared_ptr<NLREDeviceController> NLRE::getDeviceController()
{
	return _deviceController;
}

//===========================================================================================================================
std::shared_ptr<NLRETextureLoader> NLRE::getTextureLoader()
{
	return _textureLoader;
}