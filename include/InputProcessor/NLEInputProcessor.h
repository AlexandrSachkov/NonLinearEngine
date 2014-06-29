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

#ifndef NLE_INPUT_PROCESSOR_
#define NLE_INPUT_PROCESSOR_

#include <Windows.h>
#include "RenderingEngine\NLRE.h"
#include "NLEApplicationLayer.h"

class NLEInputProcessor
{
public:
	NLEInputProcessor(
		NLEWindowReference hwnd, 
		std::shared_ptr<NLEApplicationLayer> applicationLayer, 
		std::shared_ptr<NLRE> renderingEngine);
	~NLEInputProcessor();

	void processInput(LPARAM lParam);

private:
	NLEInputProcessor(const NLEInputProcessor& other);
	bool initialize();

	void processKeyboardEvent(PRAWINPUT raw, LPARAM lparam);
	void processMouseEvent(PRAWINPUT raw);
	void processEngineKeyboardControls(UINT event, UINT key, USHORT flag);
	void processGameKeyboardControls(UINT event, UINT key, USHORT flag);

	void processInputBuffered(LPARAM lParam);
	void processInputUnbuffered(LPARAM lParam);

	NLEWindowReference _hwnd;
	std::shared_ptr<NLEApplicationLayer> _applicationLayer;
	std::shared_ptr<NLRE> _renderingEngine;

	bool _gameInput;
	bool _buffered;

	float _mouseJitter;
	float _clientCenterX;
	float _clientCenterY;
};

#endif