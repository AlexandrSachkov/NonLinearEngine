#include "NL_Globals.h"

namespace NLE
{
	namespace INPUT
	{
		NLE::Queue<Event>* const GLOBAL_EVENT_QUEUE = new NLE::Queue<Event>();
	}	
}