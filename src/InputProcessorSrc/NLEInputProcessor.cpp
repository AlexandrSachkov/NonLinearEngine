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

NLEInputProcessor::NLEInputProcessor(
	NLEWindowReference hwnd, 
	std::shared_ptr<NLEApplicationLayer> applicationLayer, 
	std::shared_ptr<NLRE> renderingEngine)
{
	_hwnd = hwnd;
	_applicationLayer = applicationLayer;
	_renderingEngine = renderingEngine;
	_gameInput = false;
	_buffered = false;

	_mouseJitter = 0.0001f;
	_clientCenterX = _applicationLayer->getClientWidth() / 2;
	_clientCenterY = _applicationLayer->getClientHeight() / 2;

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
	if (!_hwnd || !_renderingEngine)
	{
		NLE_Log::err(NLE_Log::CRITICAL, "Uninitialized input parameters.");
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
	if (_buffered)
	{
		processInputBuffered(lParam);
	}
	else
	{
		processInputUnbuffered(lParam);
	}
}

void NLEInputProcessor::processInputBuffered(LPARAM lParam)
{

}

void NLEInputProcessor::processInputUnbuffered(LPARAM lParam)
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
		processKeyboardEvent(raw, lParam);
	}
	else if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		processMouseEvent(raw);
	}

	delete[] lpb;
}

void NLEInputProcessor::processKeyboardEvent(PRAWINPUT raw, LPARAM lParam)
{
	UINT scanCode = raw->data.keyboard.MakeCode;
	UINT key = MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX);
	UINT event = raw->data.keyboard.Message;
	USHORT flag = raw->data.keyboard.Flags;
	USHORT vkey = raw->data.keyboard.VKey;

	if (event == WM_KEYDOWN || event == WM_SYSKEYDOWN)
	{
		processEngineKeyboardControls(event, key, flag);
		if (_gameInput)
		{
			processGameKeyboardControls(event, key, flag);
		}
	}

	//NLE_Log::console("Scan code: %x", scanCode);
	//NLE_Log::console("Unmapped key: %i", vkey);
	//NLE_Log::console("Mapped key: %i", key);
	//NLE_Log::console("Flag: %i", flag);
	//NLE_Log::console("Event: %i\n", event);

	
}

void NLEInputProcessor::processEngineKeyboardControls(UINT event, UINT key, USHORT flag)
{
	if (key == VK_ESCAPE)
	{
		DestroyWindow(_hwnd);
	}
	if (key == VK_F1)
	{
		if (!_gameInput)
		{
			_gameInput = true;
			NLE_Log::console("Game input ON.");
		}
		else
		{
			_gameInput = false;
			NLE_Log::console("Game input OFF.");
		}
	}
}

void NLEInputProcessor::processGameKeyboardControls(UINT event, UINT key, USHORT flag)
{
	if (key == VK_F1)
	{
		_applicationLayer->setCursorPosition(_clientCenterX, _clientCenterY);
	}
	if (key == 87)
	{
		_renderingEngine->getSceneManager()->cameraMoveForward();
	}
	if (key == 83)
	{
		_renderingEngine->getSceneManager()->cameraMoveBackward();
	}
	if (key == 68)
	{
		_renderingEngine->getSceneManager()->cameraMoveRight();
	}
	if (key == 65)
	{
		_renderingEngine->getSceneManager()->cameraMoveLeft();
	}
	if (key == 69)
	{
		_renderingEngine->getSceneManager()->cameraMoveUp();
	}
	if (key == 81)
	{
		_renderingEngine->getSceneManager()->cameraMoveDown();
	}
	if (key == 82)
	{
		_renderingEngine->getSceneManager()->cameraReset();
	}
}

void NLEInputProcessor::processMouseEvent(PRAWINPUT raw)
{
	if (_gameInput)
	{
		USHORT flag;
		flag = raw->data.mouse.usFlags;

		if (flag == MOUSE_MOVE_ABSOLUTE)
		{
			//printf("absolute");
		}
		else if (flag == MOUSE_MOVE_RELATIVE)
		{

			float distX = (float)raw->data.mouse.lLastX - _clientCenterX;
			float distY = (float)raw->data.mouse.lLastY - _clientCenterY;

			if (pow(distX, 2.0) > _mouseJitter || pow(distY, 2.0) > _mouseJitter)
			{
				NLE_VECTOR velocity = NLEMath::NLEVectorSet(distX, distY, 0.0f, 0.0f);
				velocity = NLEMath::NLEVector4Normalize(velocity);
				_renderingEngine->getSceneManager()->cameraRotate(NLEMath::NLEVectorGetX(velocity), NLEMath::NLEVectorGetY(velocity));
				SetCursorPos(_clientCenterX, _clientCenterY);
			}
			
		}
	}
}
