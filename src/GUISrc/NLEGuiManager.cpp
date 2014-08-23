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

#include "RenderingEngine\NLRE.h"
#include "Application\NLEApplicationLayer.h"

#include "RenderingEngine\RenderingDevice\NLREDeviceController.h"
#include "RenderingEngine\RenderingDevice\NLRERenderingDevice.h"

#include "Input\NLEInputProcessor.h"

#include "GUI\NLECeguiInputMap.h"
#include "CEGUI\CEGUI.h"
#include "CEGUI\RendererModules\Direct3D11\Renderer.h"
#include "CEGUI\DefaultResourceProvider.h"

std::shared_ptr<NLEGuiManager> NLEGuiManager::_guiManager = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<NLEGuiManager> NLEGuiManager::instance(
	std::shared_ptr<NLRE> renderingEngine,
	std::shared_ptr<NLEApplicationLayer> appLayer
	)
{
	if (!_guiManager)
	{
		_guiManager.reset(new NLEGuiManager(renderingEngine, appLayer));
	}
	return _guiManager;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NLEGuiManager::NLEGuiManager(
	std::shared_ptr<NLRE> renderingEngine,
	std::shared_ptr<NLEApplicationLayer> appLayer
	)
{
	_renderingEngine = renderingEngine;
	_appLayer = appLayer;
	_guiRenderer = NULL;

	if (!initialize())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "GUI failed to initialize.");
		throw std::exception("GUI failed to initialize.");
	}

	NLE_Log::console("======> GUI Manager successfully initialized.");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool NLEGuiManager::initialize()
{
	std::shared_ptr<NLRERenderingDevice> renderingDevice = _renderingEngine->getDeviceController()->getRenderingDevice();
	_guiRenderer = new CEGUI::Direct3D11Renderer(CEGUI::Direct3D11Renderer::create(renderingDevice->getAPIDevice(), renderingDevice->getAPIPrimaryContext()));

	CEGUI::System::create(*_guiRenderer);
	_renderingEngine->getDeviceController()->setGuiRenderCallback(NLEGuiManager::renderGUI);


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
	{
		parser->setProperty("SchemaDefaultResourceGroup", "schemas");
	}
		
	
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

	_guiContext = &CEGUI::System::getSingleton().getDefaultGUIContext();
	_guiContext->setRootWindow(rootWindow);
	
	CEGUI::FrameWindow* fWnd = static_cast<CEGUI::FrameWindow*>(
		windowManager.createWindow("TaharezLook/FrameWindow", "testWindow"));
	rootWindow->addChild(fWnd);
	// position a quarter of the way in from the top-left of parent.
	fWnd->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0.0f), CEGUI::UDim(0.25f, 0.0f)));
	// set size to be half the size of the parent
	fWnd->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0.0f), CEGUI::UDim(0.5f, 0.0f)));
	fWnd->setText("Hello World!");
	
	NLEInputProcessor::registerInputEventListener(this);
	delete CEGUI::System::getSingleton().getClipboard()->getNativeProvider();
	CEGUI::System::getSingleton().getClipboard()->setNativeProvider(this);

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NLEGuiManager::~NLEGuiManager()
{
	NLEInputProcessor::unregisterInputEventListener(this);
	CEGUI::System::destroy();
	CEGUI::Direct3D11Renderer::destroy(*_guiRenderer);
	_guiManager = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NLEGuiManager::renderGUI()
{
	CEGUI::System::getSingleton().renderAllGUIContexts();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NLEGuiManager::processInputEvent(NLE_INPUT::Event event)
{
	switch (event.eventType)
	{
	case NLE_INPUT::EVENT_TYPE::EVENT_KEY:
		if (event.eventData.keyEvent.action == NLE_INPUT::ACTION::ACTION_PRESS)
		{
			_guiContext->injectKeyDown(NLE_INPUT::NLEtoCEGUIKey(event.eventData.keyEvent.key));
		}
		else if (event.eventData.keyEvent.action == NLE_INPUT::ACTION::ACTION_RELEASE)
		{
			_guiContext->injectKeyUp(NLE_INPUT::NLEtoCEGUIKey(event.eventData.keyEvent.key));
		}
		break;

	case NLE_INPUT::EVENT_TYPE::EVENT_CHAR:
		_guiContext->injectChar(event.eventData.charEvent.code);
		break;

	case NLE_INPUT::EVENT_TYPE::EVENT_MOUSE_BUTTON:
		if (event.eventData.mouseButtonEvent.action == NLE_INPUT::ACTION::ACTION_PRESS)
		{
			_guiContext->injectMouseButtonDown(NLE_INPUT::NLEtoCEGUIMouse(event.eventData.mouseButtonEvent.button));
		}
		else if (event.eventData.mouseButtonEvent.action == NLE_INPUT::ACTION::ACTION_RELEASE)
		{
			_guiContext->injectMouseButtonUp(NLE_INPUT::NLEtoCEGUIMouse(event.eventData.mouseButtonEvent.button));
		}
		break;

	case NLE_INPUT::EVENT_TYPE::EVENT_CURSOR_POSITION:
		_guiContext->injectMousePosition(event.eventData.cursorPositionEvent.xPos, event.eventData.cursorPositionEvent.yPos);
		break;

	case NLE_INPUT::EVENT_TYPE::EVENT_CURSOR_ENTER:
		if (event.eventData.cursorEnterEvent.entered == false)
		{
			_guiContext->injectMouseLeaves();
		}
		break;

	case NLE_INPUT::EVENT_TYPE::EVENT_SCROLL:
		_guiContext->injectMouseWheelChange(event.eventData.scrollEvent.yOffset);
		break;

	case NLE_INPUT::EVENT_TYPE::EVENT_CLIPBOARD_COPY:
		_guiContext->injectCopyRequest();
		break;

	case NLE_INPUT::EVENT_TYPE::EVENT_CLIPBOARD_CUT:
		_guiContext->injectCutRequest();
		break;

	case NLE_INPUT::EVENT_TYPE::EVENT_CLIPBOARD_PASTE:
		_guiContext->injectPasteRequest();
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NLEGuiManager::sendToClipboard(const CEGUI::String &mimeType, void *buffer, size_t size)
{
	//temporary implementation
	_appLayer->copyText(static_cast<const wchar_t*>(buffer));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NLEGuiManager::retrieveFromClipboard(CEGUI::String &mimeType, void *&buffer, size_t &size)
{
	//temporary implementation
	mimeType = "text/utf-8";
	std::wstring text = _appLayer->pasteText();
	buffer = (void*)text.c_str();
	size = text.size();
}