#ifndef NLRE_LOG_
#define NLRE_LOG_

#include "stdafx.h"

#ifdef _DEBUG || DEBUG
	#define _NLRE_debug(...) NLRE_Log::debug(__VA_ARGS__)
#else
	#define _NLRE_debug(...) 
#endif

namespace NLRE_Log
{
	enum ErrorFlag {
		CRITICAL,
		REG
	};

	std::vector <void(*)(char[])> debugCallbackList;
	std::vector <void(*)(char[])> consoleCallbackList;
	std::vector <void(*)(ErrorFlag, char[])> errCallbackList;

	void debug(const char* format, ...)
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

	void console(const char* format, ...)
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

	void err(ErrorFlag flag, const char* format, ...)
	{
		char buffer[_LOG_MSG_MAX_SIZE];
		va_list argptr;
		va_start(argptr, format);
		vsprintf(buffer, format, argptr);
		va_end(argptr);

		for each (auto callback in errCallbackList)
		{
			callback(flag,buffer);
		}
	}
}


#endif