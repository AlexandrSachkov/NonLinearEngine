#ifndef NL_SYSTEM_H_
#define NL_SYSTEM_H_

#include <cstdint>
#include "NL_Scheduler.h"

namespace NLE 
{
	namespace Core 
	{
		class SysTask;
		class Scheduler;
		class System
		{
		public:
			virtual ~System(){}

			virtual uint_fast8_t getID() = 0;
			virtual SysTask* getTask(Scheduler* scheduler) = 0;
		};
	}
}


#endif