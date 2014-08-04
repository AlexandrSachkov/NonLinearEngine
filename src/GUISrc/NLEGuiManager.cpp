/*
-----------------------------------------------------------------------------
This source file is part of NLE
(NonLinear Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearEngine

Copyright (c) 2014 NonLinear Engine Team

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
#include "GUI\NLEGuiManager.h"
#include "NLE.h"
#include "RenderingEngine\NLRE.h"
#include "CEGUI\CEGUI.h"
#include "CEGUI\RendererModules\Direct3D11\Renderer.h"
#include "RenderingEngine\RenderingDevice\NLREDeviceController.h"

NLEGuiManager::NLEGuiManager(NLE* nle)
{
	_nle = nle;
	_guiRenderer = NULL;

	if (!initialize())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "GUI failed to initialize.");
		throw std::exception("GUI failed to initialize.");
	}

	NLE_Log::console("======> GUI Manager successfully initialized.");
}

bool NLEGuiManager::initialize()
{
	std::shared_ptr<NLRERenderingDevice> renderingDevice = _nle->getRenderingEngine()->getDeviceController()->getRenderingDevice();
	_guiRenderer = new CEGUI::Direct3D11Renderer(CEGUI::Direct3D11Renderer::create(renderingDevice->getAPIDevice(), renderingDevice->getAPIPrimaryContext()));

	CEGUI::System::create(*_guiRenderer);
	_nle->getRenderingEngine()->getDeviceController()->setGuiRenderCallback(NLEGuiManager::renderGUI);

	return true;
}

NLEGuiManager::~NLEGuiManager()
{
	CEGUI::System::destroy();
	CEGUI::Direct3D11Renderer::destroy(*_guiRenderer);
}

NLEGuiManager::NLEGuiManager(const NLEGuiManager& other)
{
}

void NLEGuiManager::renderGUI()
{
	CEGUI::System::getSingleton().renderAllGUIContexts();
}