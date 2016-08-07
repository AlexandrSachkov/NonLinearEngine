#ifndef NL_GLOBALS_H_
#define NL_GLOBALS_H_

#include "NL_Queue.h"

namespace NLE
{
	namespace INPUT
	{
		struct Event;
		extern NLE::Queue<Event>* const GLOBAL_EVENT_QUEUE;
	}	
	namespace CONSOLE
	{
		class IConsoleQueue;
		extern NLE::CONSOLE::IConsoleQueue* const GLOBAL_CONSOLE_QUEUE;
	}
}

#endif