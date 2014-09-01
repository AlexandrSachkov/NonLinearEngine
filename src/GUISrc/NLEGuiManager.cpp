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

#include "RenderingEngine\RenderingDevice\NLREDeviceController.h"
#include "RenderingEngine\RenderingDevice\NLRERenderingDevice.h"

#include "Input\NLEInputProcessor.h"
#include "NLELog.h"

#include "GUI\NLECeguiInputMap.h"
#include "CEGUI\CEGUI.h"
#include "CEGUI\RendererModules\Direct3D11\Renderer.h"
#include "CEGUI\DefaultResourceProvider.h"

std::shared_ptr<NLEGuiManager> NLEGuiManager::_guiManager = nullptr;

//===========================================================================================================================
std::shared_ptr<NLEGuiManager> NLEGuiManager::instance(
	std::shared_ptr<NLRE> renderingEngine,
	std::wstring datafileRootPath
	)
{
	if (!_guiManager)
	{
		_guiManager.reset(new NLEGuiManager(renderingEngine, datafileRootPath));
	}
	return _guiManager;
}

//===========================================================================================================================
std::shared_ptr<NLEGuiManager> NLEGuiManager::instance()
{
	if (!_guiManager) throw std::runtime_error("GUI Manager is not initialized, use instance(NLE* nle)");
	return _guiManager;
}

//===========================================================================================================================
NLEGuiManager::NLEGuiManager(
	std::shared_ptr<NLRE> renderingEngine,
	std::wstring datafileRootPath
	)
{
	_renderingEngine = renderingEngine;
	_datafileRootPath = datafileRootPath;
	_guiRenderer = nullptr;
	_rootWindow = nullptr;

	if (!initialize())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "GUI failed to initialize.");
		throw std::exception("GUI failed to initialize.");
	}

	NLE_Log::console("======> GUI Manager successfully initialized.");
}

//===========================================================================================================================
bool NLEGuiManager::initialize()
{
	std::shared_ptr<NLRERenderingDevice> renderingDevice = _renderingEngine->getDeviceController()->getRenderingDevice();
	_guiRenderer = new CEGUI::Direct3D11Renderer(CEGUI::Direct3D11Renderer::create(renderingDevice->getAPIDevice(), renderingDevice->getAPIPrimaryContext()));

	CEGUI::System::create(*_guiRenderer);
	_renderingEngine->getDeviceController()->setGuiRenderCallback(NLEGuiManager::renderGUI);

	NLEInputProcessor::registerInputEventListener(this);

	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
		(CEGUI::System::getSingleton().getResourceProvider());

	fs::path datafilePath(_datafileRootPath);
	if (datafilePath.empty()) datafilePath /= "./datafiles/";

	fs::path childPath;

	childPath = datafilePath;
	childPath /= "schemes/";
	rp->setResourceGroupDirectory("schemes", childPath.generic_string());

	childPath = datafilePath;
	childPath /= "imagesets/";
	rp->setResourceGroupDirectory("imagesets", childPath.generic_string());

	childPath = datafilePath;
	childPath /= "fonts/";
	rp->setResourceGroupDirectory("fonts", childPath.generic_string());

	childPath = datafilePath;
	childPath /= "layouts/";
	rp->setResourceGroupDirectory("layouts", childPath.generic_string());

	childPath = datafilePath;
	childPath /= "looknfeel/";
	rp->setResourceGroupDirectory("looknfeels", childPath.generic_string());

	childPath = datafilePath;
	childPath /= "scripts/";
	rp->setResourceGroupDirectory("scripts", childPath.generic_string());

	childPath = datafilePath;
	childPath /= "xml_schemas/";
	rp->setResourceGroupDirectory("schemas", childPath.generic_string());
	
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
	if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
	{
		parser->setProperty("SchemaDefaultResourceGroup", "schemas");
	}
		
	
	CEGUI::ScriptModule::setDefaultResourceGroup("scripts");
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("TaharezLook/Tooltip");

	CEGUI::WindowManager& windowManager = CEGUI::WindowManager::getSingleton();
	_rootWindow = windowManager.createWindow("DefaultWindow", "root");

	_guiContext = &CEGUI::System::getSingleton().getDefaultGUIContext();
	_guiContext->setRootWindow(_rootWindow);
	
	CEGUI::FrameWindow* fWnd = static_cast<CEGUI::FrameWindow*>(
		windowManager.createWindow("TaharezLook/FrameWindow", "testWindow")
		);
	fWnd->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0.0f), CEGUI::UDim(0.25f, 0.0f)));
	fWnd->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0.0f), CEGUI::UDim(0.5f, 0.0f)));
	fWnd->setText("Hello World!");
	_rootWindow->addChild(fWnd);

	_fpsCountLabel = windowManager.createWindow("TaharezLook/Label", "fpsCount");
	_fpsCountLabel->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(0.0f, 0.0f)));
	_fpsCountLabel->setSize(CEGUI::USize(CEGUI::UDim(0.1f, 0.0f), CEGUI::UDim(0.1f, 0.0f)));
	_fpsCountLabel->setText("FPS: ");
	_rootWindow->addChild(_fpsCountLabel);

	return true;
}

//===========================================================================================================================
NLEGuiManager::~NLEGuiManager()
{
	NLEInputProcessor::unregisterInputEventListener(this);
	CEGUI::System::destroy();
	CEGUI::Direct3D11Renderer::destroy(*_guiRenderer);
	_guiManager = NULL;
}

//===========================================================================================================================
void NLEGuiManager::updateUI()
{
	if (_renderingEngine->fpsChanged())
	{
		CEGUI::String message = "FPS: ";
		message.append(std::to_string(_renderingEngine->getFPS()));
		_fpsCountLabel->setText(message);
	}
}

//===========================================================================================================================
void NLEGuiManager::showFPS(bool option)
{
	if (option) _fpsCountLabel->show();
	else _fpsCountLabel->hide();
}

//===========================================================================================================================
void NLEGuiManager::renderGUI()
{
	CEGUI::System::getSingleton().renderAllGUIContexts();
}

//===========================================================================================================================
void NLEGuiManager::processInputEvent(NLE_INPUT::Event event)
{
	switch (event.eventType)
	{
	case NLE_INPUT::EVENT_TYPE::EVENT_KEY:
		if (event.eventData.keyEvent.action == NLE_INPUT::ACTION::ACTION_PRESS)
		{
			_guiContext->injectKeyDown(static_cast<CEGUI::Key::Scan>(NLE_INPUT::NLEtoCEGUIKey(event.eventData.keyEvent.key)));
		}
		else if (event.eventData.keyEvent.action == NLE_INPUT::ACTION::ACTION_RELEASE)
		{
			_guiContext->injectKeyUp(static_cast<CEGUI::Key::Scan>(NLE_INPUT::NLEtoCEGUIKey(event.eventData.keyEvent.key)));
		}
		break;

	case NLE_INPUT::EVENT_TYPE::EVENT_CHAR:
		_guiContext->injectChar(event.eventData.charEvent.code);
		break;

	case NLE_INPUT::EVENT_TYPE::EVENT_MOUSE_BUTTON:
		if (event.eventData.mouseButtonEvent.action == NLE_INPUT::ACTION::ACTION_PRESS)
		{
			_guiContext->injectMouseButtonDown(static_cast<CEGUI::MouseButton>(NLE_INPUT::NLEtoCEGUIMouse(event.eventData.mouseButtonEvent.button)));
		}
		else if (event.eventData.mouseButtonEvent.action == NLE_INPUT::ACTION::ACTION_RELEASE)
		{
			_guiContext->injectMouseButtonUp(static_cast<CEGUI::MouseButton>(NLE_INPUT::NLEtoCEGUIMouse(event.eventData.mouseButtonEvent.button)));
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

	case NLE_INPUT::EVENT_WINDOW_SIZE:
		CEGUI::Sizef size(
			event.eventData.windowSizeEvent.width,
			event.eventData.windowSizeEvent.height
			);
		CEGUI::System::getSingleton().notifyDisplaySizeChanged(size);
	}
}
