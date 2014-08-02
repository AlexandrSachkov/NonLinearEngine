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
#include "NLEApplicationLayer.h"
#include "NLE.h"
#include "RenderingEngine\NLRE.h"
#include "RenderingEngine\SceneManager\NLRESceneManager.h"
#include "InputProcessor\NLEInputProcessor.h"

#include "SDL.h"
#include "SDL_syswm.h"


NLE* nle = nullptr;

NLEApplicationLayer::NLEApplicationLayer(NLE* nle)
{
	_nle = nle;
	_window = nullptr;
	_sysInfo = nullptr;

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
	if (_sysInfo) delete _sysInfo;

	SDL_DestroyWindow(_window);
	SDL_Quit();
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

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		NLE_Log::err(NLE_Log::CRITICAL, "SDL failed to initialize: %s\n", SDL_GetError());
		return false;
	}

	_window = SDL_CreateWindow("NonLinear Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1900, 1000, SDL_WINDOW_SHOWN);
	if (_window == NULL)
	{
		NLE_Log::err(NLE_Log::CRITICAL, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	if (!getWindowInfo())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "Window information could not be retrieved: %s\n", SDL_GetError());
		return false;
	}


	NLE_Log::console("======> Application Layer successfully initialized.");
	return true;
}

bool NLEApplicationLayer::getWindowInfo()
{
	_sysInfo = new SDL_SysWMinfo();
	SDL_VERSION(&_sysInfo->version);
	if (!SDL_GetWindowWMInfo(_window, _sysInfo))
	{
		return false;
	}

	const char *subsystem = "an unknown system!";
	switch (_sysInfo->subsystem) {
	case SDL_SYSWM_UNKNOWN:   break;
	case SDL_SYSWM_WINDOWS:   
		subsystem = "Microsoft Windows(TM)";  
		_windowRef = static_cast<NLEWindowReference>(_sysInfo->info.win.window);
		break;
	case SDL_SYSWM_X11:       subsystem = "X Window System";        break;
#if SDL_VERSION_ATLEAST(2, 0, 3)
	case SDL_SYSWM_WINRT:     subsystem = "WinRT";                  break;
#endif
	case SDL_SYSWM_DIRECTFB:  subsystem = "DirectFB";               break;
	case SDL_SYSWM_COCOA:     subsystem = "Apple OS X";             break;
	case SDL_SYSWM_UIKIT:     subsystem = "UIKit";                  break;
#if SDL_VERSION_ATLEAST(2, 0, 2)
	case SDL_SYSWM_WAYLAND:   subsystem = "Wayland";                break;
	case SDL_SYSWM_MIR:       subsystem = "Mir";                    break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 4)
	case SDL_SYSWM_ANDROID:   subsystem = "Android";                break;
#endif
	}

	NLE_Log::console("This program is running SDL version %d.%d.%d on %s\n",
		(int)_sysInfo->version.major,
		(int)_sysInfo->version.minor,
		(int)_sysInfo->version.patch,
		subsystem);
	return true;
}

int NLEApplicationLayer::runMessageLoop()
{
	SDL_Event event;
	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			else
			{
				_nle->getInputProcessor()->processEvent(&event);
			}
		}

		//=========================== for testing only
		_nle->getRenderingEngine()->getSceneManager()->cameraUpdate();
		_nle->getRenderingEngine()->render();
	}
	return 0;
}

NLEWindowReference& NLEApplicationLayer::getWindowReference()
{
	return _windowRef;
}

void NLEApplicationLayer::getClientSize(int& width, int& height)
{
	SDL_GetWindowSize(_window,&width, &height);
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
		MessageBox(nullptr, L"NonLinear Engine failed to start.", L"ERROR", MB_OK);
		delete nle;
		return 0;
	}
	nle->run();
	delete nle;

	return 0;
}