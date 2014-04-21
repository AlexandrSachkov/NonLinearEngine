#include "stdafx.h"
#include "NLRE.h"

NLRE::NLRE(){
	
}

NLRE::~NLRE(){

}

void NLRE::registerDebugCallback(void(*callback)(char msg[]))
{
	NLRE_Log::debugCallbackList.push_back(callback);
}

void NLRE::registerConsoleCallback(void(*callback)(char msg[]))
{
	NLRE_Log::consoleCallbackList.push_back(callback);
}

void NLRE::registerErrorCallback(void(*callback)(char msg[]))
{
	NLRE_Log::errCallbackList.push_back(callback);
}

void NLRE::unregisterDebugCallback(void(*callback)(char msg[]))
{
	for (std::vector<void(*)(char[])>::iterator it = NLRE_Log::debugCallbackList.begin();
		it != NLRE_Log::debugCallbackList.end(); ++it)
	{
		if (*it == callback)
		{
			NLRE_Log::debugCallbackList.erase(it);
		}
	}
}

void NLRE::unregisterConsoleCallback(void(*callback)(char msg[]))
{
	for (std::vector<void(*)(char[])>::iterator it = NLRE_Log::consoleCallbackList.begin();
		it != NLRE_Log::consoleCallbackList.end(); ++it)
	{
		if (*it == callback)
		{
			NLRE_Log::consoleCallbackList.erase(it);
		}
	}
}

void NLRE::unregisterErrorCallback(void(*callback)(char msg[]))
{
	for (std::vector<void(*)(char[])>::iterator it = NLRE_Log::errCallbackList.begin();
		it != NLRE_Log::errCallbackList.end(); ++it)
	{
		if (*it == callback)
		{
			NLRE_Log::errCallbackList.erase(it);
		}
	}
}

void NLRE::unregisterDebugCallbackAll()
{
	NLRE_Log::debugCallbackList.empty();
}

void NLRE::unregisterConsoleCallbackAll()
{
	NLRE_Log::consoleCallbackList.empty();
}

void NLRE::unregisterErrorCallbackAll()
{
	NLRE_Log::errCallbackList.empty();
}