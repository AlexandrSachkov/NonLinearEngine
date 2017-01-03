#ifndef NL_GLOBALS_H_
#define NL_GLOBALS_H_

#include "NL_Queue.h"
#include "NL_IConsoleQueue.h"
#include <memory>

namespace NLE
{
	namespace INPUT
	{
		struct Event;
		extern std::shared_ptr<NLE::Queue<Event>> GLOBAL_EVENT_QUEUE;
	}	
	namespace CONSOLE
	{
		class IConsoleQueue;
		extern IConsoleQueueSP GLOBAL_CONSOLE_QUEUE;
	}
}

#endif