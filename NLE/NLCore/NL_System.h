#ifndef NL_SYSTEM_H_
#define NL_SYSTEM_H_

#include <cstdint>

namespace NLE 
{
	namespace Core 
	{
		class SysTask;
		class System
		{
		public:
			virtual ~System(){}

			virtual uint_fast8_t getID() = 0;
			virtual SysTask* getTask() = 0;
		};
	}
}


#endif