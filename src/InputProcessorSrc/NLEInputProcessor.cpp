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
#include "InputProcessor\NLEInputProcessor.h"

NLEInputProcessor::NLEInputProcessor(NLEWindowReference hwnd)
{
	_hwnd = hwnd;

	if (!initialize())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "NLE Input Processor failed to initialize.");
		throw std::exception("NLE Input Processor failed to initialize.");
	}
	NLE_Log::console("======> NLEInputProcessor successfully initialized.");
}

NLEInputProcessor::NLEInputProcessor(const NLEInputProcessor& other)
{

}

NLEInputProcessor::~NLEInputProcessor()
{

}

bool NLEInputProcessor::initialize()
{
	if (!_hwnd)
	{
		NLE_Log::err(NLE_Log::CRITICAL, "Window reference is uninitialized");
		return false;
	}

	RAWINPUTDEVICE rid[2];

	rid[0].usUsagePage = 1;
	rid[0].usUsage = 2;
	rid[0].dwFlags = 0;
	rid[0].hwndTarget = _hwnd;

	rid[1].usUsagePage = 1;
	rid[1].usUsage = 6;
	rid[1].dwFlags = 0;
	rid[1].hwndTarget = _hwnd;

	LPTSTR errorText = NULL;
	
	if (RegisterRawInputDevices(rid, 2, sizeof(rid[0])) == FALSE) {
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&errorText,
			0,
			NULL);

		if (errorText != NULL)
		{
			NLE_Log::err(NLE_Log::CRITICAL, "Input devices failed to register.");
			LocalFree(errorText);
			errorText = NULL;
		}
		return false;
	}
	
	return true;
}

void NLEInputProcessor::processInput(LPARAM lParam)
{
	UINT dwSize;
	if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER)) == -1){
		return;
	}
	LPBYTE lpb = new BYTE[dwSize];
	if (lpb == NULL){
		return;
	}
	if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize){
		delete[] lpb;
		return;
	}
	PRAWINPUT raw = (PRAWINPUT)lpb;

	if (raw->header.dwType == RIM_TYPEKEYBOARD)
	{
		processKeyboardEvent(raw);
	}
	else if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		processMouseEvent(raw);
	}
}

void NLEInputProcessor::processKeyboardEvent(PRAWINPUT raw)
{
	UINT event;
	WCHAR keyNum;

	event = raw->data.keyboard.Message;

	if (event == WM_KEYDOWN)
	{
		keyNum = MapVirtualKey(raw->data.keyboard.VKey, MAPVK_VK_TO_CHAR);

		if (keyNum == 27)
		{
			DestroyWindow(_hwnd);
		}
	}

}

void NLEInputProcessor::processMouseEvent(PRAWINPUT raw)
{
	printf("Mouse event");
}
