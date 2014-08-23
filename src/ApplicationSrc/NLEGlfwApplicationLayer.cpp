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
#include "Application\NLEGlfwApplicationLayer.h"
#include "NLE.h"
#include "RenderingEngine\NLRE.h"
#include "RenderingEngine\SceneManager\NLRESceneManager.h"
#include "GUI\NLEGuiManager.h"
#include "Input\NLEInputEvents.h"
#include "Application\NLEGlfwInputMap.h"
#include "Input\NLEInputProcessor.h"

#include "GLFW\glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include "GLFW\glfw3native.h"

std::shared_ptr<NLEGlfwApplicationLayer> NLEGlfwApplicationLayer::_glfwAppLayer = NULL;

std::shared_ptr<NLEGlfwApplicationLayer> NLEGlfwApplicationLayer::instance()
{
	if (!_glfwAppLayer)
	{
		_glfwAppLayer.reset(new NLEGlfwApplicationLayer());
	}
	return _glfwAppLayer;
}


NLEGlfwApplicationLayer::NLEGlfwApplicationLayer()
{
	_nle = NULL;
	_title = "NonLinear Engine";

	_width = 0;
	_height = 0;

	if (!initialize())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "Application Layer failed to initialize");
		throw std::exception("Application Layer failed to initialize");
	}
}

NLEGlfwApplicationLayer::~NLEGlfwApplicationLayer()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

bool NLEGlfwApplicationLayer::initialize()
{
	NLE_Log::registerErrorCallback(NLEGlfwApplicationLayer::errorCallback);
	NLE_Log::registerConsoleCallback(NLEGlfwApplicationLayer::debugCallback);
	NLE_Log::registerDebugCallback(NLEGlfwApplicationLayer::debugCallback);
	
	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "GLFW failed to initialize.");
		return false;
	}

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	_width = mode->width;
	_height = mode->height;

	_window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
	if (!_window)
	{
		glfwTerminate();
		NLE_Log::err(NLE_Log::CRITICAL, "Window failed to initialize.");
		return false;
	}

	glfwSetKeyCallback(_window, onKeyEvent);
	glfwSetCharCallback(_window, onCharEvent);
	glfwSetMouseButtonCallback(_window, onMouseButtonEvent);
	glfwSetCursorPosCallback(_window, onCursorPositionEvent);
	glfwSetCursorEnterCallback(_window, onCursorEnterEvent);
	glfwSetScrollCallback(_window, onScrollEvent);

	glfwSetWindowPosCallback(_window, onWindowPositionEvent);
	glfwSetWindowSizeCallback(_window, onWindowSizeEvent);
	glfwSetWindowCloseCallback(_window, onWindowCloseEvent);
	glfwSetWindowRefreshCallback(_window, onWindowRefreshEvent);
	glfwSetWindowFocusCallback(_window, onWindowFocusEvent);
	glfwSetWindowIconifyCallback(_window, onWindowIconifyEvent);

	NLE_Log::console("======> Application Layer successfully initialized.");
	return true;
}

void NLEGlfwApplicationLayer::initNLE()
{
	_nle = NLE::instance(
		std::dynamic_pointer_cast<NLEApplicationLayer>(NLEGlfwApplicationLayer::instance()), 
		std::dynamic_pointer_cast<NLEInputSupply>(NLEGlfwApplicationLayer::instance())
		);
}



NLEWindowReference& NLEGlfwApplicationLayer::getWindowReference()
{
	NLEWindowReference windowRef = glfwGetWin32Window(_window);
	return windowRef;
}

void NLEGlfwApplicationLayer::getClientSize(int& width, int& height)
{
	glfwGetWindowSize(_window, &width, &height);
}

void NLEGlfwApplicationLayer::setClientSize(int width, int height)
{
	glfwSetWindowSize(_window, width, height);
}

void NLEGlfwApplicationLayer::setFullscreen(bool option)
{
	
}

void NLEGlfwApplicationLayer::setResizableHint(bool option)
{
	glfwWindowHint(GLFW_RESIZABLE, option == true ? GL_TRUE : GL_FALSE);
}

void NLEGlfwApplicationLayer::setDecoratedHint(bool option)
{
	glfwWindowHint(GLFW_DECORATED, option == true ? GL_TRUE : GL_FALSE);
}

void NLEGlfwApplicationLayer::setTitle(std::wstring title)
{
	std::string textOut(title.begin(), title.end());
	glfwSetWindowTitle(_window, textOut.c_str());
}

void NLEGlfwApplicationLayer::setWindowPosition(int x, int y)
{
	glfwSetWindowPos(_window, x, y);
}

void NLEGlfwApplicationLayer::getWindowPosition(int& x, int& y)
{
	glfwGetWindowPos(_window, &x, &y);
}

void NLEGlfwApplicationLayer::iconify()
{
	glfwIconifyWindow(_window);
}

void NLEGlfwApplicationLayer::restore()
{
	glfwRestoreWindow(_window);
}

void NLEGlfwApplicationLayer::show()
{
	glfwShowWindow(_window);
}

void NLEGlfwApplicationLayer::hide()
{
	glfwHideWindow(_window);
}

int NLEGlfwApplicationLayer::runMessageLoop()
{
	if (!_nle) throw std::runtime_error("Unable to run, engine must be initialized");

	_nle->run();
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();

		_nle->onTick();
	}
	_nle->stop();

	return 0;
}

void NLEGlfwApplicationLayer::closeWindow()
{
	glfwSetWindowShouldClose(_window, GL_TRUE);
}




void NLEGlfwApplicationLayer::copyText(std::wstring text)
{
	std::string textOut(text.begin(), text.end());
	glfwSetClipboardString(_window, textOut.c_str());
}

std::wstring NLEGlfwApplicationLayer::pasteText()
{
	std::string text(glfwGetClipboardString(_window));
	std::wstring textOut(text.begin(), text.end());
	return textOut;
}

std::shared_ptr<NLE> NLEGlfwApplicationLayer::getNLE()
{
	return _nle;
}

bool NLEGlfwApplicationLayer::bindInputEventCallback(void(*processEvent)(NLE_INPUT::Event event))
{
	if (processEvent)
	{
		_processEvent = processEvent;
		return true;
	}
	return false;
}

void NLEGlfwApplicationLayer::errorCallback(NLE_Log::ErrorFlag flag, char text[])
{
	printf(text);
	printf("\n");
}

void NLEGlfwApplicationLayer::debugCallback(char text[])
{
	printf(text);
	printf("\n");
}

void NLEGlfwApplicationLayer::consoleCallback(char text[])
{
	printf(text);
	printf("\n");
}

void NLEGlfwApplicationLayer::glfwErrorCallback(int error, const char* description)
{
	NLE_Log::err(NLE_Log::REG, "Application Layer Error: %i, %s", error, description);
}



void NLEGlfwApplicationLayer::onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_KEY;
	event.eventData.keyEvent.action = NLE_INPUT::GLFWtoNLEAction(action);
	event.eventData.keyEvent.key = NLE_INPUT::GLFWtoNLEKey(key);
	event.eventData.keyEvent.mods = NLE_INPUT::GLFWtoNLEMod(mods);
	event.eventData.keyEvent.scancode = scancode;

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onCharEvent(GLFWwindow *window, unsigned int codepoint)
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_CHAR;
	event.eventData.charEvent.code = codepoint;

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onMouseButtonEvent(GLFWwindow *window, int button, int action, int mods)
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_MOUSE_BUTTON;
	event.eventData.mouseButtonEvent.action = NLE_INPUT::GLFWtoNLEAction(action);
	event.eventData.mouseButtonEvent.button = NLE_INPUT::GLFWtoNLEMouse(button);
	event.eventData.mouseButtonEvent.mods = NLE_INPUT::GLFWtoNLEMod(mods);

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onCursorPositionEvent(GLFWwindow *window, double xPos, double yPos)
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_CURSOR_POSITION;
	event.eventData.cursorPositionEvent.xPos = xPos;
	event.eventData.cursorPositionEvent.yPos = yPos;

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onCursorEnterEvent(GLFWwindow *window, int entered)
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_CURSOR_ENTER;
	event.eventData.cursorEnterEvent.entered = entered == GL_TRUE ? true : false;

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onScrollEvent(GLFWwindow *window, double xOffset, double yOffset)
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_SCROLL;
	event.eventData.scrollEvent.xOffset = xOffset;
	event.eventData.scrollEvent.yOffset = yOffset;

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onWindowPositionEvent(GLFWwindow *window, int xPos, int yPos)
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_WINDOW_POSITION;
	event.eventData.windowPositionEvent.xPos = xPos;
	event.eventData.windowPositionEvent.yPos = yPos;

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onWindowSizeEvent(GLFWwindow *window, int width, int height)
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_WINDOW_SIZE;
	event.eventData.windowSizeEvent.width = width;
	event.eventData.windowSizeEvent.height = height;

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onWindowCloseEvent(GLFWwindow *window)
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_WINDOW_CLOSE;
	
	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onWindowRefreshEvent(GLFWwindow *window)
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_WINDOW_REFRESH;

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onWindowFocusEvent(GLFWwindow *window, int focused)
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_WINDOW_FOCUS;
	event.eventData.windowFocusEvent.focused = focused == GL_TRUE ? true : false;

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onWindowIconifyEvent(GLFWwindow *window, int iconified)
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_WINDOW_ICONIFY;
	event.eventData.windowIconifyEvent.iconified = iconified == GL_TRUE ? true : false;

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onClipboardCopyEvent()
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_CLIPBOARD_COPY;

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onClipboardCutEvent()
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_CLIPBOARD_CUT;

	_glfwAppLayer->_processEvent(event);
}

void NLEGlfwApplicationLayer::onClipboardPasteEvent()
{
	NLE_INPUT::Event event;
	event.eventType = NLE_INPUT::EVENT_TYPE::EVENT_CLIPBOARD_PASTE;

	_glfwAppLayer->_processEvent(event);
}




int main(int argc, const char* argv[])
{
	std::shared_ptr<NLEGlfwApplicationLayer> appLayer = NULL;
	std::shared_ptr<NLE> nle = NULL;
	try
	{
		appLayer = NLEGlfwApplicationLayer::instance();
		appLayer->initNLE();
	}
	catch (std::exception& e)
	{
		std::wstring errTxt = L"NonLinear Engine failed to start: ";
		std::string errMsgStr(e.what());
		std::wstring errMsg(errMsgStr.begin(), errMsgStr.end());
		errTxt.append(errMsg);
		printf("NonLinear engine ERROR: ", errTxt.c_str());
		return 0;
	}
	appLayer->runMessageLoop();
	return 0;
}