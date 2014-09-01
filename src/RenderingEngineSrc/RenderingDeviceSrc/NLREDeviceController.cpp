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
#include "RenderingEngine\RenderingDevice\NLREDeviceController.h"
#include "RenderingEngine\RenderingDevice\NLRERenderingDevice.h"
#include "RenderingEngine\RenderingDevice\NLREForwardRT.h"

NLREDeviceController::NLREDeviceController(NLEWindowReference hwnd, int width, int height, bool fullScreen, NLRE_RENDERING_TECHNIQUE_ID techniqueId)
{
	_renderingTechniqueId = techniqueId;
	_guiRenderCallback = NULL;
	_renderingDevice.reset(new NLRERenderingDevice(hwnd, width, height, fullScreen));
	if (!initialize())
	{
		NLRE_Log::err(NLRE_Log::CRITICAL, "Device controller failed to initialize");
		throw std::exception("Device controller failed to initialize");
	}
}

NLREDeviceController::~NLREDeviceController()
{
}


bool NLREDeviceController::initialize()
{
	if (!setRenderingTechnique(_renderingTechniqueId)) return false;
	return true;
}

std::shared_ptr<NLRERenderingDevice> NLREDeviceController::getRenderingDevice()
{
	return _renderingDevice;
}

bool NLREDeviceController::setRenderingTechnique(NLRE_RENDERING_TECHNIQUE_ID techniqueId)
{
	_renderingTechniqueId = techniqueId;
	try
	{
		switch (techniqueId)
		{
		case NLRE_FORWARD_RT:
			_renderingTechnique.reset(new NLREForwardRT(getRenderingDevice()));
			break;
		default:
			throw std::exception("Unsupported Rendering Technique.");
		}
	}
	catch (std::exception& e)
	{
		return false;
	}
	return true;
}

NLRE_RENDERING_TECHNIQUE_ID NLREDeviceController::getCurrentRenderingTechniqueId()
{
	return _renderingTechniqueId;
}

void NLREDeviceController::render(std::vector<std::shared_ptr<NLRE_RenderableAsset>>& assets)
{
	_renderingTechnique->render(assets);
	if (_guiRenderCallback)
	{
		_guiRenderCallback();
	}
	_renderingDevice->display();
}

void NLREDeviceController::setGuiRenderCallback(void(*guiRenderCallback)(void))
{
	_guiRenderCallback = guiRenderCallback;
}