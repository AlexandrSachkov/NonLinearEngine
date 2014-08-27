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
#include "NLELog.h"

std::shared_ptr<NLE_Log> NLE_Log::_nleLog = NULL;

std::vector <void(*)(char[])> NLE_Log::debugCallbackList;
std::vector <void(*)(char[])> NLE_Log::consoleCallbackList;
std::vector <void(*)(NLE_Log::ErrorFlag, char[])> NLE_Log::errCallbackList;

std::shared_ptr<NLE_Log> NLE_Log::instance()
{
	if (!_nleLog)
	{
		_nleLog.reset(new NLE_Log());
	}
	return _nleLog;
}

NLE_Log::NLE_Log()
{

}

NLE_Log::~NLE_Log()
{
	unregisterDebugCallbackAll();
	unregisterConsoleCallbackAll();
	unregisterErrorCallbackAll();
}

void NLE_Log::debug(const char* format, ...)
{
	char buffer[_LOG_MSG_MAX_SIZE];
	va_list argptr;
	va_start(argptr, format);
	vsprintf(buffer, format, argptr);
	va_end(argptr);

	for each (auto callback in debugCallbackList)
	{
		callback(buffer);
	}
}

void NLE_Log::console(const char* format, ...)
{
	char buffer[_LOG_MSG_MAX_SIZE];
	va_list argptr;
	va_start(argptr, format);
	vsprintf(buffer, format, argptr);
	va_end(argptr);

	for each (auto callback in consoleCallbackList)
	{
		callback(buffer);
	}
}

void NLE_Log::err(ErrorFlag flag, const char* format, ...)
{
	char buffer[_LOG_MSG_MAX_SIZE];
	va_list argptr;
	va_start(argptr, format);
	vsprintf(buffer, format, argptr);
	va_end(argptr);

	for each (auto callback in errCallbackList)
	{
		callback(flag, buffer);
	}
}


void NLE_Log::registerDebugCallback(void(*callback)(char msg[]))
{
	debugCallbackList.push_back(callback);
}

void NLE_Log::registerConsoleCallback(void(*callback)(char msg[]))
{
	consoleCallbackList.push_back(callback);
}

void NLE_Log::registerErrorCallback(void(*callback)(NLE_Log::ErrorFlag, char msg[]))
{
	errCallbackList.push_back(callback);
}

void NLE_Log::unregisterDebugCallback(void(*callback)(char msg[]))
{
	for (std::vector<void(*)(char[])>::iterator it = debugCallbackList.begin();
		it != debugCallbackList.end(); ++it)
	{
		if (*it == callback)
		{
			debugCallbackList.erase(it);
		}
	}
}

void NLE_Log::unregisterConsoleCallback(void(*callback)(char msg[]))
{
	for (std::vector<void(*)(char[])>::iterator it = consoleCallbackList.begin();
		it != consoleCallbackList.end(); ++it)
	{
		if (*it == callback)
		{
			consoleCallbackList.erase(it);
		}
	}
}

void NLE_Log::unregisterErrorCallback(void(*callback)(NLE_Log::ErrorFlag, char msg[]))
{
	for (std::vector<void(*)(NLE_Log::ErrorFlag, char[])>::iterator it = errCallbackList.begin();
		it != errCallbackList.end(); ++it)
	{
		if (*it == callback)
		{
			errCallbackList.erase(it);
		}
	}
}

void NLE_Log::unregisterDebugCallbackAll()
{
	debugCallbackList.empty();
}

void NLE_Log::unregisterConsoleCallbackAll()
{
	consoleCallbackList.empty();
}

void NLE_Log::unregisterErrorCallbackAll()
{
	errCallbackList.empty();
}