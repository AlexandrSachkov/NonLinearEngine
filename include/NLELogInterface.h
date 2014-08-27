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

#ifndef NLE_LOG_INTERFACE_
#define NLE_LOG_INTERFACE_

class NLELogInterface
{
public:
	enum ErrorFlag {
		CRITICAL,
		REG
	};
	virtual ~NLELogInterface(){}
	virtual void registerDebugCallback(void(*callback)(char msg[])) =0;
	virtual void registerConsoleCallback(void(*callback)(char msg[])) =0;
	virtual void registerErrorCallback(void(*callback)(ErrorFlag flag, char msg[])) =0;
	virtual void unregisterDebugCallback(void(*callback)(char msg[])) =0;
	virtual void unregisterConsoleCallback(void(*callback)(char msg[])) =0;
	virtual void unregisterErrorCallback(void(*callback)(ErrorFlag flag, char msg[])) =0;
};

#endif