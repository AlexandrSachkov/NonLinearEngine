#include "stdafx.h"

std::vector <void(*)(char[])> NLRE_Log::debugCallbackList;
std::vector <void(*)(char[])> NLRE_Log::consoleCallbackList;
std::vector <void(*)(NLRE_Log::ErrorFlag, char[])> NLRE_Log::errCallbackList;

void NLRE_Log::debug(const char* format, ...)
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

void NLRE_Log::console(const char* format, ...)
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

void NLRE_Log::err(ErrorFlag flag, const char* format, ...)
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


void NLRE_Log::registerDebugCallback(void(*callback)(char msg[]))
{
	debugCallbackList.push_back(callback);
}

void NLRE_Log::registerConsoleCallback(void(*callback)(char msg[]))
{
	consoleCallbackList.push_back(callback);
}

void NLRE_Log::registerErrorCallback(void(*callback)(NLRE_Log::ErrorFlag, char msg[]))
{
	errCallbackList.push_back(callback);
}

void NLRE_Log::unregisterDebugCallback(void(*callback)(char msg[]))
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

void NLRE_Log::unregisterConsoleCallback(void(*callback)(char msg[]))
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

void NLRE_Log::unregisterErrorCallback(void(*callback)(NLRE_Log::ErrorFlag, char msg[]))
{
	for (std::vector<void(*)(NLRE_Log::ErrorFlag, char[])>::iterator it = errCallbackList.begin();
		it != errCallbackList.end(); ++it)
	{
		if (*it == callback)
		{
			errCallbackList.erase(it);
		}
	}
}

void NLRE_Log::unregisterDebugCallbackAll()
{
	debugCallbackList.empty();
}

void NLRE_Log::unregisterConsoleCallbackAll()
{
	consoleCallbackList.empty();
}

void NLRE_Log::unregisterErrorCallbackAll()
{
	errCallbackList.empty();
}