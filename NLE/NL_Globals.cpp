#include "NL_Globals.h"
#include "NL_InputEvents.h"
#include "NL_ConsoleQueue.h"

namespace NLE
{
	namespace INPUT
	{
		NLE::Queue<Event>* const GLOBAL_EVENT_QUEUE = new NLE::Queue<Event>();
	}	
	namespace CONSOLE
	{
		NLE::CONSOLE::IConsoleQueue* const GLOBAL_CONSOLE_QUEUE = new NLE::CONSOLE::ConsoleQueue();
	}
}