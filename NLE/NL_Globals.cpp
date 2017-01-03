#include "NL_Globals.h"
#include "NL_InputEvents.h"
#include "NL_ConsoleQueue.h"

namespace NLE
{
	namespace INPUT
	{
		std::shared_ptr<NLE::Queue<Event>> GLOBAL_EVENT_QUEUE = std::make_shared<Queue<Event>>();
	}	
	namespace CONSOLE
	{
		IConsoleQueueSP GLOBAL_CONSOLE_QUEUE = std::make_shared<CONSOLE::ConsoleQueue>();
	}
}