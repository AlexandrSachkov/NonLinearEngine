/*
-----------------------------------------------------------------------------
This source file is part of NLE
(NonLinear Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearEngine

Copyright (c) 2015 Alexandr Sachkov

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

#include "NL_GlfwWindowManager.h"
#include "NL_GlfwInputMap.h"
#include "NL_ThreadLocal.h"
#include "NL_Globals.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_INCLUDE_NONE
#include "GLFW\glfw3.h"
#include "GLFW/glfw3native.h"

#include <assert.h>

namespace NLE
{
	GlfwWindowManager::GlfwWindowManager(CONSOLE::IConsoleQueue_EServiceSP console) :
		_console(console)
	{
		_window = nullptr;
	}

	GlfwWindowManager::~GlfwWindowManager()
	{
		if (_window)
			glfwDestroyWindow(_window);
		glfwTerminate();
	}


	bool GlfwWindowManager::initialize(
		Size2D screenSize,
		bool fullscreen,
		bool decorated,
		std::wstring title
		)
	{
		_fullScreen = fullscreen;

		glfwSetErrorCallback(glfwErrorCallback);
		if (!glfwInit())
		{
			_console->push(CONSOLE::ERR, "GLFW failed to initialize");
			return false;
		}

		setResizableHint(false);
		setDecoratedHint(decorated);

		TLS::StringConverter::reference converter = TLS::strConverter.local();
		if (fullscreen)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			_window = glfwCreateWindow(mode->width, mode->height, converter.to_bytes(title).c_str(), glfwGetPrimaryMonitor(), NULL);
		}
		else
		{
			_window = glfwCreateWindow(screenSize.width, screenSize.height, converter.to_bytes(title).c_str(), NULL, NULL);
		}
			

		if (!_window)
		{
			glfwTerminate();
			_console->push(CONSOLE::ERR, "Window failed to initialize");
			return false;
		}
		setWindowCallbacks(_window);
		enableCursor(true);

		return true;
	}

	void GlfwWindowManager::setWindowCallbacks(GLFWwindow* window)
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

	void GlfwWindowManager::enableCursor(bool enable)
	{
		glfwSetInputMode(_window, GLFW_CURSOR, enable == true ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	}

	Size2D GlfwWindowManager::getClientSize()
	{
		int width, height;
		glfwGetWindowSize(_window, &width, &height);
		return Size2D(width, height);
	}

	void* GlfwWindowManager::getWindowHandle()
	{
		return (void*)glfwGetWin32Window(_window);
	}

	bool GlfwWindowManager::getFullScreen()
	{
		return _fullScreen;
	}

	void GlfwWindowManager::setResizableHint(bool option)
	{
		glfwWindowHint(GLFW_RESIZABLE, option);
	}

	void GlfwWindowManager::setDecoratedHint(bool option)
	{
		glfwWindowHint(GLFW_DECORATED, option);
	}

	void GlfwWindowManager::setTitle(std::wstring title)
	{
		TLS::StringConverter::reference converter = TLS::strConverter.local();
		glfwSetWindowTitle(_window, converter.to_bytes(title).c_str());
	}

	void GlfwWindowManager::setWindowPosition(Position2D position)
	{
		glfwSetWindowPos(_window, position.x, position.y);
	}

	Position2D GlfwWindowManager::getWindowPosition()
	{
		int x, y;
		glfwGetWindowPos(_window, &x, &y);
		return Position2D(x, y);
	}

	void GlfwWindowManager::iconify()
	{
		glfwIconifyWindow(_window);
	}

	void GlfwWindowManager::restore()
	{
		glfwRestoreWindow(_window);
	}

	void GlfwWindowManager::show()
	{
		glfwShowWindow(_window);
	}

	void GlfwWindowManager::hide()
	{
		glfwHideWindow(_window);
	}

	void GlfwWindowManager::closeWindow()
	{
		glfwSetWindowShouldClose(_window, true);
	}

	void GlfwWindowManager::copyText(std::wstring text)
	{
		std::string textOut(text.begin(), text.end());
		glfwSetClipboardString(_window, textOut.c_str());
	}

	std::wstring GlfwWindowManager::pasteText()
	{
		std::string text(glfwGetClipboardString(_window));
		std::wstring textOut(text.begin(), text.end());
		return textOut;
	}

	void GlfwWindowManager::glfwErrorCallback(int error, const char* description)
	{
		std::string errCode;
		if (error == GLFW_NO_CURRENT_CONTEXT)
			errCode = "GLFW_NO_CURRENT_CONTEXT";
		else if (error == GLFW_OUT_OF_MEMORY)
			errCode = "GLFW_OUT_OF_MEMORY";
		else if (error == GLFW_PLATFORM_ERROR)
			errCode = "GLFW_PLATFORM_ERROR";
		else if (error == GLFW_VERSION_UNAVAILABLE)
			errCode = "GLFW_VERSION_UNAVAILABLE";
		else if (error == GLFW_FORMAT_UNAVAILABLE)
			errCode = "GLFW_FORMAT_UNAVAILABLE";

		printf("%s, %s\n", errCode.c_str(), description);
	}

	void GlfwWindowManager::onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		NLE::INPUT::Event event;
		event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_KEY;
		event.eventData.keyEvent.action = NLE::INPUT::GLFWtoNLEAction(action);
		event.eventData.keyEvent.key = NLE::INPUT::GLFWtoNLEKey(key);
		event.eventData.keyEvent.mods = NLE::INPUT::GLFWtoNLEMod(mods);
		event.eventData.keyEvent.scancode = scancode;

		processEvent(event);
	}

	void GlfwWindowManager::onCharEvent(GLFWwindow *window, unsigned int codepoint)
	{
		NLE::INPUT::Event event;
		event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_CHAR;
		event.eventData.charEvent.code = codepoint;

		processEvent(event);
	}

	void GlfwWindowManager::onMouseButtonEvent(GLFWwindow *window, int button, int action, int mods)
	{
		NLE::INPUT::Event event;
		event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_MOUSE_BUTTON;
		event.eventData.mouseButtonEvent.action = NLE::INPUT::GLFWtoNLEAction(action);
		event.eventData.mouseButtonEvent.button = NLE::INPUT::GLFWtoNLEMouse(button);
		event.eventData.mouseButtonEvent.mods = NLE::INPUT::GLFWtoNLEMod(mods);

		processEvent(event);
	}

	void GlfwWindowManager::onCursorPositionEvent(GLFWwindow *window, double xPos, double yPos)
	{
		NLE::INPUT::Event event;
		event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_CURSOR_POSITION;
		event.eventData.cursorPositionEvent.xPos = xPos;
		event.eventData.cursorPositionEvent.yPos = yPos;

		processEvent(event);
	}

	void GlfwWindowManager::onCursorEnterEvent(GLFWwindow *window, int entered)
	{
		NLE::INPUT::Event event;
		event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_CURSOR_ENTER;
		event.eventData.cursorEnterEvent.entered = entered == 1 ? true : false;

		processEvent(event);
	}

	void GlfwWindowManager::onScrollEvent(GLFWwindow *window, double xOffset, double yOffset)
	{
		NLE::INPUT::Event event;
		event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_SCROLL;
		event.eventData.scrollEvent.xOffset = xOffset;
		event.eventData.scrollEvent.yOffset = yOffset;

		processEvent(event);
	}

	void GlfwWindowManager::onWindowPositionEvent(GLFWwindow *window, int xPos, int yPos)
	{
		NLE::INPUT::Event event;
		event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_WINDOW_POSITION;
		event.eventData.windowPositionEvent.xPos = xPos;
		event.eventData.windowPositionEvent.yPos = yPos;

		processEvent(event);
	}

	void GlfwWindowManager::onWindowSizeEvent(GLFWwindow *window, int width, int height)
	{
		NLE::INPUT::Event event;
		event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_WINDOW_SIZE;
		event.eventData.windowSizeEvent.width = width;
		event.eventData.windowSizeEvent.height = height;

		processEvent(event);
	}

	void GlfwWindowManager::onWindowCloseEvent(GLFWwindow *window)
	{
		NLE::INPUT::Event event;
		event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_WINDOW_CLOSE;

		processEvent(event);
	}

	void GlfwWindowManager::onWindowRefreshEvent(GLFWwindow *window)
	{
		NLE::INPUT::Event event;
		event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_WINDOW_REFRESH;

		processEvent(event);
	}

	void GlfwWindowManager::onWindowFocusEvent(GLFWwindow *window, int focused)
	{
		NLE::INPUT::Event event;
		event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_WINDOW_FOCUS;
		event.eventData.windowFocusEvent.focused = focused == 1 ? true : false;

		processEvent(event);
	}

	void GlfwWindowManager::onWindowIconifyEvent(GLFWwindow *window, int iconified)
	{
		NLE::INPUT::Event event;
		event.eventType = NLE::INPUT::EVENT_TYPE::EVENT_WINDOW_ICONIFY;
		event.eventData.windowIconifyEvent.iconified = iconified == 1 ? true : false;

		processEvent(event);
	}

	void GlfwWindowManager::processEvent(INPUT::Event& event)
	{
		INPUT::GLOBAL_EVENT_QUEUE->push(event);
	}

	void GlfwWindowManager::makeContextCurrent(bool makeCurrent)
	{
		glfwMakeContextCurrent(makeCurrent == true ? _window : NULL);
	}

	void GlfwWindowManager::enableVSync(bool enable)
	{
		glfwSwapInterval(enable == true ? 1 : 0);
	}

	void GlfwWindowManager::swapBuffers()
	{
		glfwSwapBuffers(_window);
	}

	void GlfwWindowManager::pollEvents()
	{
		glfwPollEvents();
	}
}
