#ifndef NLRE_LOG_
#define NLRE_LOG_

#include "stdafx.h"

#ifdef _DEBUG || DEBUG
#define _NLRE_debug(...) NLRE_Log::debug(__VA_ARGS__)
#else
#define _NLRE_debug(...) 
#endif



class NLRE_Log
{

public:

	enum ErrorFlag {
		CRITICAL,
		REG
	};
	static void debug(const char* format, ...);
	static void console(const char* format, ...);
	static void err(ErrorFlag flag, const char* format, ...);
	static void registerDebugCallback(void(*callback)(char msg[]));
	static void registerConsoleCallback(void(*callback)(char msg[]));
	static void registerErrorCallback(void(*callback)(NLRE_Log::ErrorFlag, char msg[]));
	static void unregisterDebugCallback(void(*callback)(char msg[]));
	static void unregisterConsoleCallback(void(*callback)(char msg[]));
	static void unregisterErrorCallback(void(*callback)(NLRE_Log::ErrorFlag, char msg[]));
	static void unregisterDebugCallbackAll();
	static void unregisterConsoleCallbackAll();
	static void unregisterErrorCallbackAll();


	static std::vector <void(*)(char[])> debugCallbackList;
	static std::vector <void(*)(char[])> consoleCallbackList;
	static std::vector <void(*)(NLRE_Log::ErrorFlag, char[])> errCallbackList;
};


#endif