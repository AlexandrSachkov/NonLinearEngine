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

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>

#include "NLE.h"

NLE* nle = NULL;

void debugCallback(char text[]);
void consoleCallback(char text[]);
void errorCallback(NLE_Log::ErrorFlag flag, char text[]);

int messageloop();
void releaseResources(NLE* nle);
bool initializeWindow(HINSTANCE hInstance, int width, int height, HWND& hwnd);
LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	AllocConsole();
	freopen("CONOUT$", "wb", stdout);

	HWND hwnd = NULL;
	int width = GetSystemMetrics(SM_CXMAXIMIZED);
	int height = GetSystemMetrics(SM_CYMAXIMIZED);

	NLE_Log::registerErrorCallback(errorCallback);
	NLE_Log::registerConsoleCallback(debugCallback);
	NLE_Log::registerDebugCallback(debugCallback);

	if (!initializeWindow(hInstance, width, height, hwnd))
	{
		MessageBox(0, L"Window Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	try
	{
		nle = new NLE(hwnd, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	}
	catch (std::exception& e)
	{
		MessageBox(0, L"NonLinear Engine failed to initialize",
			L"Error", MB_OK);
		releaseResources(nle);
		return 0;
	}

	messageloop();
	releaseResources(nle);
	return 0;
}

bool initializeWindow(HINSTANCE hInstance, int width, int height, HWND& hwnd)
{
	WNDCLASSEX wc;
	std::wstring windowClassName = L"mainWindow";

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
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

	hwnd = CreateWindowEx(
		NULL,
		windowClassName.c_str(),
		L"NonLinear Engine",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hwnd)
	{
		return false;
	}

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	return true;
}

int messageloop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	int counter = 0;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

void releaseResources(NLE* nle)
{
	if (nle) delete nle;

	fclose(stdout);
	FreeConsole();
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INPUT:
		nle->processInput(lParam);
		return 0;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


void errorCallback(NLE_Log::ErrorFlag flag, char text[])
{
	printf(text);
	printf("\n");
}

void debugCallback(char text[])
{
	printf(text);
	printf("\n");
}

void consoleCallback(char text[])
{
	printf(text);
	printf("\n");
}