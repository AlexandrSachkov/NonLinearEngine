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
#include "NLEApplicationLayer.h"
#include "NLE.h"
#include "RenderingEngine\NLRE.h"
#include "RenderingEngine\SceneManager\NLRESceneManager.h"
#include "GUI\NLEGuiManager.h"

#include "GLFW\glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include "GLFW\glfw3native.h"


NLE* nle = nullptr;

NLEApplicationLayer::NLEApplicationLayer(NLE* nle)
{
	_nle = nle;


	if (!initialize())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "Application Layer failed to initialize");
		throw std::exception("Application Layer failed to initialize");
	}
}

NLEApplicationLayer::NLEApplicationLayer(const NLEApplicationLayer& other)
{
}

NLEApplicationLayer::~NLEApplicationLayer()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
	fclose(stdout);
	FreeConsole();
}

bool NLEApplicationLayer::initialize()
{
	AllocConsole();
	freopen("CONOUT$", "wb", stdout);

	NLE_Log::registerErrorCallback(NLEApplicationLayer::errorCallback);
	NLE_Log::registerConsoleCallback(NLEApplicationLayer::debugCallback);
	NLE_Log::registerDebugCallback(NLEApplicationLayer::debugCallback);

	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "GLFW failed to initialize.");
		return false;
	}

	_window = glfwCreateWindow(1900, 1000, "NonLinear Engine", NULL, NULL);
	if (!_window)
	{
		glfwTerminate();
		NLE_Log::err(NLE_Log::CRITICAL, "Window failed to initialize.");
		return false;
	}

	NLE_Log::console("======> Application Layer successfully initialized.");
	return true;
}


int NLEApplicationLayer::runMessageLoop()
{
	
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();

		//=========================== for testing only
		_nle->getRenderingEngine()->getSceneManager()->cameraUpdate();
		_nle->getRenderingEngine()->render();
	}
		
	return 0;
}

void NLEApplicationLayer::endMessageLoop()
{
	glfwSetWindowShouldClose(_window, GL_TRUE);
}

void NLEApplicationLayer::copyClipboard(std::wstring text)
{
	std::string textOut(text.begin(), text.end());
	glfwSetClipboardString(_window, textOut.c_str());
}

void NLEApplicationLayer::cutClipboard(std::wstring text)
{
	copyClipboard(text);
}

std::wstring NLEApplicationLayer::pasteClipboard()
{
	std::string text(glfwGetClipboardString(_window));
	std::wstring textOut(text.begin(), text.end());
	return textOut;
}


NLEWindowReference& NLEApplicationLayer::getWindowReference()
{
	NLEWindowReference windowRef = glfwGetWin32Window(_window);
	return windowRef;
}

void NLEApplicationLayer::getClientSize(int& width, int& height)
{
	glfwGetWindowSize(_window, &width, &height);
}

void NLEApplicationLayer::setClientSize(int width, int height)
{
	glfwSetWindowSize(_window, width, height);
}

void NLEApplicationLayer::setResizableHint(bool option)
{
	if (option)
	{
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	}
	else
	{
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}
	
}

void NLEApplicationLayer::setDecoratedHint(bool option)
{
	if (option)
	{
		glfwWindowHint(GLFW_DECORATED, GL_TRUE);
	}
	else
	{
		glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	}
}

void NLEApplicationLayer::setTitle(std::wstring title)
{
	std::string textOut(title.begin(), title.end());
	glfwSetWindowTitle(_window, textOut.c_str());
}

void NLEApplicationLayer::setPosition(int x, int y)
{
	glfwSetWindowPos(_window, x, y);
}

void NLEApplicationLayer::getPosition(int& x, int& y)
{
	glfwGetWindowPos(_window, &x, &y);
}

void NLEApplicationLayer::iconify()
{
	glfwIconifyWindow(_window);
}

void NLEApplicationLayer::restore()
{
	glfwRestoreWindow(_window);
}

void NLEApplicationLayer::show()
{
	glfwShowWindow(_window);
}

void NLEApplicationLayer::hide()
{
	glfwHideWindow(_window);
}


void NLEApplicationLayer::errorCallback(NLE_Log::ErrorFlag flag, char text[])
{
	printf(text);
	printf("\n");
}

void NLEApplicationLayer::debugCallback(char text[])
{
	printf(text);
	printf("\n");
}

void NLEApplicationLayer::consoleCallback(char text[])
{
	printf(text);
	printf("\n");
}

void NLEApplicationLayer::glfwErrorCallback(int error, const char* description)
{
	NLE_Log::err(NLE_Log::REG, "Application Layer Error: %i, %s", error, description);
}

GLFWwindow* NLEApplicationLayer::getGLFWwindow()
{
	return _window;
}


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	try
	{
		nle = new NLE();
	}
	catch (std::exception& e)
	{
		std::wstring errTxt = L"NonLinear Engine failed to start: ";
		std::string errMsgStr(e.what());
		std::wstring errMsg(errMsgStr.begin(), errMsgStr.end());
		errTxt.append(errMsg);
		MessageBox(nullptr, errTxt.c_str(), L"ERROR", MB_OK);
		delete nle;
		return 0;
	}
	nle->run();
	delete nle;

	return 0;
}