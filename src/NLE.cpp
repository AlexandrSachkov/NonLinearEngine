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
#include "NLE.h"

NLE::NLE(NLEWindowReference winRef, int width, int height)
{
	_winRef = winRef;
	_width = width;
	_height = height;

	NLRE_Log::registerDebugCallback(NLE::NLREdebugOutputHook);
	NLRE_Log::registerConsoleCallback(NLE::NLREconsoleOutputHook);
	NLRE_Log::registerErrorCallback(NLE::NLREerrorOutputHook);

	_renderingEngine.reset(new NLRE(winRef, width, height));
}

NLE::NLE(const NLE& other)
{

	if (!initialize())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "NonLinear Engine failed to initialize");
		throw std::exception("NonLinear Engine failed to initialize");
	}
}

NLE::~NLE()
{

}

bool NLE::initialize()
{
	if (!_winRef)
	{
		NLE_Log::err(NLE_Log::CRITICAL, "Window Reference is uninitialized");
		return false;
	}
	return true;
}

void NLE::NLREdebugOutputHook(char text[])
{
	NLE_Log::debug(text);
}

void NLE::NLREconsoleOutputHook(char text[])
{
	NLE_Log::console(text);
}

void NLE::NLREerrorOutputHook(NLRE_Log::ErrorFlag flag, char text[])
{
	NLE_Log::err((NLE_Log::ErrorFlag)flag, text);
}

void NLE::run()
{

}
