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
#include "NLE.h"
#include "Application\NLEGlfwApplicationLayer.h"
#include "RenderingEngine\NLRE.h"
#include "Input\NLEInputProcessor.h"
#include "Input\NLEInputSupply.h"
#include "GUI\NLEGuiManager.h"

std::shared_ptr<NLE> NLE::_nle = NULL;

std::shared_ptr<NLE> NLE::instance()
{
	if (!_nle)
	{
		_nle.reset(new NLE());
	}
	return _nle;
}

NLE::NLE()
{
	NLRE_Log::registerDebugCallback(NLE::NLREdebugOutputHook);
	NLRE_Log::registerConsoleCallback(NLE::NLREconsoleOutputHook);
	NLRE_Log::registerErrorCallback(NLE::NLREerrorOutputHook);

	_applicationLayer = std::dynamic_pointer_cast<NLEApplicationLayer>(NLEGlfwApplicationLayer::instance(this));
	_inputSupply = std::dynamic_pointer_cast<NLEInputSupply>(NLEGlfwApplicationLayer::instance(this));

	_applicationLayer->getClientSize(_width, _height);

	_renderingEngine.reset(new NLRE(_applicationLayer->getWindowReference(), _width, _height));
	_guiManager = NLEGuiManager::instance(this, _applicationLayer);
	_inputProcessor = NLEInputProcessor::instance(this, _applicationLayer, _inputSupply);
	

	//======================= FOR TESTING PURPOSES =================
	std::wstring path = L"D:\\3DModels\\Altair Model\\altair2.dae";
	_renderingEngine->importAsset(path);
	//==============================================================

	if (!initialize())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "NonLinear Engine failed to initialize");
		throw std::exception("NonLinear Engine failed to initialize");
	}

	NLE_Log::console("======> NLE successfully initialized.");
}

NLE::~NLE()
{

}

bool NLE::initialize()
{
	
	return true;
}

void NLE::NLREdebugOutputHook(char text[])
{
	NLE_Log::debug(text);
}

void NLE::NLREconsoleOutputHook(char text[])
{
	NLE_Log::console(text);
}

void NLE::NLREerrorOutputHook(NLRE_Log::ErrorFlag flag, char text[])
{
	NLE_Log::err((NLE_Log::ErrorFlag)flag, text);
}

void NLE::run()
{
	//======================= FOR TESTING PURPOSES =================
	_applicationLayer->runMessageLoop();
	//==============================================================
}

bool NLE::bindApplicationLayer(std::shared_ptr<NLEApplicationLayer> appLayer)
{
	if (!appLayer) return false;
	_applicationLayer = appLayer;
	return true;
}

bool NLE::bindInputSupply(std::shared_ptr<NLEInputSupply> inputSupply)
{

	return false;
}

std::shared_ptr<NLRE> NLE::getRenderingEngine()
{
	return _renderingEngine;
}

std::shared_ptr<NLEInputProcessor> NLE::getInputProcessor()
{
	return _inputProcessor;
}

std::shared_ptr<NLEApplicationLayer> NLE::getApplicationLayer()
{
	return _applicationLayer;
}

std::shared_ptr<NLEGuiManager> NLE::getGuiManager()
{
	return _guiManager;
}

