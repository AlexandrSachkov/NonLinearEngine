#ifndef NL_GLOBALS_H_
#define NL_GLOBALS_H_

#include "NL_Queue.h"
#include "NL_InputEvents.h"

namespace NLE
{
	namespace INPUT
	{
		extern NLE::Queue<Event>* const GLOBAL_EVENT_QUEUE; //needed to pass events from static callbacks of GLFW to InputManager
	}	
}

#endif