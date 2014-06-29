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

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

NLE* nle = nullptr;

NLEApplicationLayer::NLEApplicationLayer(HINSTANCE hInstance, NLE* nle)
{
	_hInstance = hInstance;
	_nle = nle;
	_hwnd = nullptr;
	_screenWidth = 0;
	_screenHeight = 0;
	_clientWidth = 0;
	_clientHeight = 0;

	if (!initialize())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "Application Layer failed to initialize");
		throw std::exception("Application Layer failed to initialize");
	}
}

NLEApplicationLayer::NLEApplicationLayer(const NLEApplicationLayer& other)
{
}

bool NLEApplicationLayer::initialize()
{
	AllocConsole();
	freopen("CONOUT$", "wb", stdout);

	NLE_Log::registerErrorCallback(NLEApplicationLayer::errorCallback);
	NLE_Log::registerConsoleCallback(NLEApplicationLayer::debugCallback);
	NLE_Log::registerDebugCallback(NLEApplicationLayer::debugCallback);

	if (!initializeWindow())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "Window failed to initialize");
		return false;
	}	
	
	updateClientDimensions();
	updateScreenDimensions();

	NLE_Log::console("======> Application Layer successfully initialized.");
	return true;
}


NLEApplicationLayer::~NLEApplicationLayer()
{
	fclose(stdout);
	FreeConsole();
}

bool NLEApplicationLayer::initializeWindow()
{
	WNDCLASSEX wc;
	std::wstring windowClassName = L"mainWindow";

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = NLEApplicationLayer::wndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = _hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = windowClassName.c_str();
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	_hwnd = CreateWindowEx(
		NULL,
		windowClassName.c_str(),
		L"NonLinear Engine",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		_screenWidth, _screenHeight,
		NULL,
		NULL,
		_hInstance,
		NULL
		);

	if (!_hwnd)
	{
		return false;
	}

	ShowWindow(_hwnd, SW_MAXIMIZE);
	UpdateWindow(_hwnd);

	return true;
}

int NLEApplicationLayer::runMessageLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	int counter = 0;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		//======================= FOR TESTING PURPOSES =================
		_nle->getRenderingEngine()->render();
		_nle->getRenderingEngine()->getSceneManager()->cameraUpdate();
		//==============================================================
	}
	return msg.wParam;
}

LRESULT CALLBACK NLEApplicationLayer::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg)
	{	
	case WM_INPUT:
		nle->getInputProcessor()->processInput(lParam);
		return 0;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
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

void NLEApplicationLayer::displayErrorBox(std::wstring title, std::wstring message)
{
	MessageBox(_hwnd, message.c_str(), title.c_str(), MB_OK);
}

NLEWindowReference& NLEApplicationLayer::getWindowReference()
{
	return _hwnd;
}

int NLEApplicationLayer::getScreenWidth()
{
	return _screenWidth;
}

int NLEApplicationLayer::getScreenHeight()
{
	return _screenHeight;
}

void NLEApplicationLayer::updateScreenDimensions()
{
	_screenWidth = GetSystemMetrics(SM_CXMAXIMIZED);
	_screenHeight = GetSystemMetrics(SM_CYMAXIMIZED);
}

int NLEApplicationLayer::getClientWidth()
{
	return _clientWidth;
}

int NLEApplicationLayer::getClientHeight()
{
	return _clientHeight;
}

void NLEApplicationLayer::updateClientDimensions()
{
	RECT clientRect;
	GetClientRect(_hwnd, &clientRect);
	_clientWidth = clientRect.right - clientRect.left;
	_clientHeight = clientRect.bottom - clientRect.top;
}

void NLEApplicationLayer::setCursorPosition(float x, float y)
{
	SetCursorPos(x, y);
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	try
	{
		nle = new NLE(hInstance);
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