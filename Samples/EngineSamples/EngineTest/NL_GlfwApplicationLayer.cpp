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

#include "NL_GlfwApplicationLayer.h"
#include "NL_GlfwInputMap.h"
#include "NLE\NL_Nle.h"

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <assert.h>

NLEGlfwApplicationLayer* NLEGlfwApplicationLayer::_glfwAppLayer = nullptr;

//===========================================================================================================================
NLEGlfwApplicationLayer& NLEGlfwApplicationLayer::instance()
{
	if (!_glfwAppLayer)
	{
		_glfwAppLayer = new NLEGlfwApplicationLayer();
	}
	return *_glfwAppLayer;
}

//===========================================================================================================================
NLEGlfwApplicationLayer::NLEGlfwApplicationLayer()
{
	_nle = NULL;
	_title = "NonLinear Engine";

	_width = 0;
	_height = 0;
	_window = NULL;
	_fullscreen = true;
}

//===========================================================================================================================
NLEGlfwApplicationLayer::~NLEGlfwApplicationLayer()
{
	if (_nle)
		_nle->release();
	glfwDestroyWindow(_window);
	glfwTerminate();
}

//===========================================================================================================================
bool NLEGlfwApplicationLayer::initialize()
{
	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit())
	{
		printf("GLFW failed to initialize.\n");
		return false;
	}

	if (_fullscreen || _width == 0 || _height == 0)
	{
		const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		_width = mode->width;
		_height = mode->height;
	}

	setResizableHint(false);

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	if (_fullscreen)
	{
		_window = glfwCreateWindow(_width, _height, _title.c_str(), glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		_window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
	}

	if (!_window)
	{
		glfwTerminate();
		printf("Window failed to initialize.\n");
		return false;
	}
	setWindowCallbacks(_window);

	glfwMakeContextCurrent(_window); // Initialize GLEW 
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize GLEW\n");
		return false;
	}

	_nle = NLE::instance();

	_nle->attachPollEvents([&](){
		if (!glfwWindowShouldClose(_window))
		{
			glfwPollEvents();
		}
		else
		{
			_nle->stop();
		}					
	});
	
	_nle->attachMakeContextCurrent([&](){
		glfwMakeContextCurrent(_window);
	}); 

	_nle->attachSwapBuffers([&](){
		glfwSwapBuffers(_window);
	});

	if (!_nle->initialize()) return false;

	printf("======> Application Layer successfully initialized.\n");
	return true;
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::setWindowCallbacks(GLFWwindow* window)
{
	glfwSetKeyCallback(window, onKeyEvent);
	glfwSetCharCallback(window, onCharEvent);
	glfwSetMouseButtonCallback(window, onMouseButtonEvent);
	glfwSetCursorPosCallback(window, onCursorPositionEvent);
	glfwSetCursorEnterCallback(window, onCursorEnterEvent);
	glfwSetScrollCallback(window, onScrollEvent);

	glfwSetWindowPosCallback(window, onWindowPositionEvent);
	glfwSetWindowSizeCallback(window, onWindowSizeEvent);
	glfwSetWindowCloseCallback(window, onWindowCloseEvent);
	glfwSetWindowRefreshCallback(window, onWindowRefreshEvent);
	glfwSetWindowFocusCallback(window, onWindowFocusEvent);
	glfwSetWindowIconifyCallback(window, onWindowIconifyEvent);
}

//===========================================================================================================================
NLE::INle* NLEGlfwApplicationLayer::getNLE()
{
	return _nle;
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::getClientSize(int& width, int& height)
{
	glfwGetWindowSize(_window, &width, &height);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::setWindowSizeHint(int width, int height)
{
	_width = width;
	_height = height;
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::setFullscreenHint(bool option)
{
	_fullscreen = option;
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::setResizableHint(bool option)
{
	glfwWindowHint(GLFW_RESIZABLE, option == true ? GL_TRUE : GL_FALSE);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::setDecoratedHint(bool option)
{
	glfwWindowHint(GLFW_DECORATED, option == true ? GL_TRUE : GL_FALSE);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::setTitle(std::wstring title)
{
	std::string textOut(title.begin(), title.end());
	glfwSetWindowTitle(_window, textOut.c_str());
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::setWindowPosition(int x, int y)
{
	glfwSetWindowPos(_window, x, y);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::getWindowPosition(int& x, int& y)
{
	glfwGetWindowPos(_window, &x, &y);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::iconify()
{
	glfwIconifyWindow(_window);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::restore()
{
	glfwRestoreWindow(_window);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::show()
{
	glfwShowWindow(_window);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::hide()
{
	glfwHideWindow(_window);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::run()
{
	_nle->run();
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::closeWindow()
{
	glfwSetWindowShouldClose(_window, GL_TRUE);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::copyText(std::wstring text)
{
	std::string textOut(text.begin(), text.end());
	glfwSetClipboardString(_window, textOut.c_str());
}

//===========================================================================================================================
std::wstring NLEGlfwApplicationLayer::pasteText()
{
	std::string text(glfwGetClipboardString(_window));
	std::wstring textOut(text.begin(), text.end());
	return textOut;
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::glfwErrorCallback(int error, const char* description)
{
	printf("Application Layer Error: %i, %s", error, description);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE) _glfwAppLayer->closeWindow();

	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_KEY;
	event.eventData.keyEvent.action = NLE::INPUT::GLFWtoNLEAction(action);
	event.eventData.keyEvent.key = NLE::INPUT::GLFWtoNLEKey(key);
	event.eventData.keyEvent.mods = NLE::INPUT::GLFWtoNLEMod(mods);
	event.eventData.keyEvent.scancode = scancode;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onCharEvent(GLFWwindow *window, unsigned int codepoint)
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_CHAR;
	event.eventData.charEvent.code = codepoint;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onMouseButtonEvent(GLFWwindow *window, int button, int action, int mods)
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_MOUSE_BUTTON;
	event.eventData.mouseButtonEvent.action = NLE::INPUT::GLFWtoNLEAction(action);
	event.eventData.mouseButtonEvent.button = NLE::INPUT::GLFWtoNLEMouse(button);
	event.eventData.mouseButtonEvent.mods = NLE::INPUT::GLFWtoNLEMod(mods);

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onCursorPositionEvent(GLFWwindow *window, double xPos, double yPos)
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_CURSOR_POSITION;
	event.eventData.cursorPositionEvent.xPos = xPos;
	event.eventData.cursorPositionEvent.yPos = yPos;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onCursorEnterEvent(GLFWwindow *window, int entered)
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_CURSOR_ENTER;
	event.eventData.cursorEnterEvent.entered = entered == GL_TRUE ? true : false;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onScrollEvent(GLFWwindow *window, double xOffset, double yOffset)
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_SCROLL;
	event.eventData.scrollEvent.xOffset = xOffset;
	event.eventData.scrollEvent.yOffset = yOffset;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onWindowPositionEvent(GLFWwindow *window, int xPos, int yPos)
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_WINDOW_POSITION;
	event.eventData.windowPositionEvent.xPos = xPos;
	event.eventData.windowPositionEvent.yPos = yPos;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onWindowSizeEvent(GLFWwindow *window, int width, int height)
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_WINDOW_SIZE;
	event.eventData.windowSizeEvent.width = width;
	event.eventData.windowSizeEvent.height = height;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onWindowCloseEvent(GLFWwindow *window)
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_WINDOW_CLOSE;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onWindowRefreshEvent(GLFWwindow *window)
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_WINDOW_REFRESH;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onWindowFocusEvent(GLFWwindow *window, int focused)
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_WINDOW_FOCUS;
	event.eventData.windowFocusEvent.focused = focused == GL_TRUE ? true : false;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onWindowIconifyEvent(GLFWwindow *window, int iconified)
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_WINDOW_ICONIFY;
	event.eventData.windowIconifyEvent.iconified = iconified == GL_TRUE ? true : false;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onClipboardCopyEvent()
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_CLIPBOARD_COPY;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onClipboardCutEvent()
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_CLIPBOARD_CUT;

	_glfwAppLayer->getNLE()->processEvent(event);
}

//===========================================================================================================================
void NLEGlfwApplicationLayer::onClipboardPasteEvent()
{
	NLE::INPUT::Event event;
	event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_CLIPBOARD_PASTE;

	_glfwAppLayer->getNLE()->processEvent(event);
}