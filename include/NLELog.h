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

#ifndef NLE_LOG_
#define NLE_LOG_

#include "NLELogInterface.h"
#include "NLEDllApi.h"
#include <memory>
#include <vector>

#ifdef _DEBUG || DEBUG
#define _NLE_debug(...) NLE_Log::debug(__VA_ARGS__)
#else
#define _NLE_debug(...) 
#endif



class NLE_Log : public NLELogInterface
{

public:
	static std::shared_ptr<NLE_Log> instance();
	~NLE_Log();

	static void debug(const char* format, ...);
	static void console(const char* format, ...);
	static void err(ErrorFlag flag, const char* format, ...);

	void registerDebugCallback(void(*callback)(char msg[]));
	void registerConsoleCallback(void(*callback)(char msg[]));
	void registerErrorCallback(void(*callback)(NLE_Log::ErrorFlag, char msg[]));
	void unregisterDebugCallback(void(*callback)(char msg[]));
	void unregisterConsoleCallback(void(*callback)(char msg[]));
	void unregisterErrorCallback(void(*callback)(NLE_Log::ErrorFlag, char msg[]));

	static void unregisterDebugCallbackAll();
	static void unregisterConsoleCallbackAll();
	static void unregisterErrorCallbackAll();

private:
	NLE_Log();
	NLE_Log(const NLE_Log& other){}
	NLE_Log& operator=(const NLE_Log&){}

	static std::shared_ptr<NLE_Log> _nleLog;

	static std::vector <void(*)(char[])> debugCallbackList;
	static std::vector <void(*)(char[])> consoleCallbackList;
	static std::vector <void(*)(NLE_Log::ErrorFlag, char[])> errCallbackList;
};

#endif