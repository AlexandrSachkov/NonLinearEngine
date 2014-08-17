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
#include "GUI\NLEGuiManager.h"
#include "NLE.h"
#include "RenderingEngine\NLRE.h"
#include "RenderingEngine\RenderingDevice\NLREDeviceController.h"
#include "RenderingEngine\RenderingDevice\NLRERenderingDevice.h"
#include "InputProcessor\NLEInputProcessor.h"
#include "InputProcessor\NLECeguiInputMap.h"
#include "InputProcessor\NLECeguiInputMap.h"

#include "CEGUI\CEGUI.h"
#include "CEGUI\RendererModules\Direct3D11\Renderer.h"
#include "CEGUI\DefaultResourceProvider.h"

std::shared_ptr<NLEGuiManager> NLEGuiManager::_guiManager = NULL;

std::shared_ptr<NLEGuiManager> NLEGuiManager::instance(NLE* nle)
{
	if (!_guiManager)
	{
		_guiManager.reset(new NLEGuiManager(nle));
	}
	return _guiManager;
}

std::shared_ptr<NLEGuiManager> NLEGuiManager::instance()
{
	if (!_guiManager)
	{
		throw std::runtime_error("GUI Manager is not initialized, use instance(NLE* nle)");
	}
	else
	{
		return _guiManager;
	}
}


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


	// initialise the required dirs for the DefaultResourceProvider
	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
		(CEGUI::System::getSingleton().getResourceProvider());
	rp->setResourceGroupDirectory("schemes", "../datafiles/schemes/");
	rp->setResourceGroupDirectory("imagesets", "../datafiles/imagesets/");
	rp->setResourceGroupDirectory("fonts", "../datafiles/fonts/");
	rp->setResourceGroupDirectory("layouts", "../datafiles/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "../datafiles/looknfeel/");
	rp->setResourceGroupDirectory("scripts", "../datafiles/scripts/");

	// This is only really needed if you are using Xerces and need to
	// specify the schemas location
	rp->setResourceGroupDirectory("schemas", "../datafiles/xml_schemas/");
	
	// set the default resource groups to be used
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	// setup default group for validation schemas
	CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
	if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
		parser->setProperty("SchemaDefaultResourceGroup", "schemas");
	
	CEGUI::ScriptModule::setDefaultResourceGroup("scripts");

	// create (load) the TaharezLook scheme file
	// (this auto-loads the TaharezLook looknfeel and imageset files)
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	// create (load) a font.
	// The first font loaded automatically becomes the default font, but note
	// that the scheme might have already loaded a font, so there may already
	// be a default set - if we want the "DejaVuSans-10" font to definitely
	// be the default, we should set the default explicitly afterwards.
	CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
	CEGUI::System::getSingleton().getDefaultGUIContext().
		getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	CEGUI::System::getSingleton().getDefaultGUIContext().
		setDefaultTooltipType("TaharezLook/Tooltip");

	CEGUI::WindowManager& windowManager = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* rootWindow = windowManager.createWindow("DefaultWindow", "root");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(rootWindow);
	
	CEGUI::FrameWindow* fWnd = static_cast<CEGUI::FrameWindow*>(
		windowManager.createWindow("TaharezLook/FrameWindow", "testWindow"));
	rootWindow->addChild(fWnd);
	// position a quarter of the way in from the top-left of parent.
	fWnd->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0.0f), CEGUI::UDim(0.25f, 0.0f)));
	// set size to be half the size of the parent
	fWnd->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0.0f), CEGUI::UDim(0.5f, 0.0f)));
	fWnd->setText("Hello World!");
	
	NLEInputProcessor::registerInputListener(this);
	return true;
}

NLEGuiManager::~NLEGuiManager()
{
	CEGUI::System::destroy();
	CEGUI::Direct3D11Renderer::destroy(*_guiRenderer);
	_guiManager = NULL;
}


void NLEGuiManager::renderGUI()
{
	CEGUI::System::getSingleton().renderAllGUIContexts();
}

void NLEGuiManager::onKeyEvent(NLE_INPUT::KEY key, int scancode, NLE_INPUT::ACTION action, NLE_INPUT::MOD mods)
{
	
	if (action == NLE_INPUT::ACTION::PRESS)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(NLE_INPUT::NLEtoCEGUIKey(key));
	}
	else
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(NLE_INPUT::NLEtoCEGUIKey(key));
	}
}

void NLEGuiManager::onCharEvent(unsigned int codepoint)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(codepoint);
}

void NLEGuiManager::onMouseButtonEvent(NLE_INPUT::MOUSE button, NLE_INPUT::ACTION action, NLE_INPUT::MOD mods)
{
	if (action == NLE_INPUT::ACTION::PRESS)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(NLE_INPUT::NLEtoCEGUIMouse(button));
	}
	else
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(NLE_INPUT::NLEtoCEGUIMouse(button));
	}
}

void NLEGuiManager::onCursorPositionEvent(double xPos, double yPos)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(xPos, yPos);
}

void NLEGuiManager::onCursorEnterEvent(bool entered)
{
	if (!entered)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseLeaves();
	}
}

void NLEGuiManager::onScrollEvent(double xOffset, double yOffset)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange(yOffset);
}
