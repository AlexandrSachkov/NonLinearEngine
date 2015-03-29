#ifndef NL_SYSTEM_H_
#define NL_SYSTEM_H_

#include <cstdint>
#include <memory>

namespace NLE 
{
	namespace Core 
	{
		class SysTask;
		class Scheduler;
		class SysData;
		class System
		{
		public:
			virtual ~System(){}

			virtual bool initialize(uint_fast8_t id) = 0;
			virtual void release() = 0;

			virtual uint_fast8_t getID() = 0;
			virtual SysTask* getTask(
				std::unique_ptr<Scheduler> const& scheduler,
				std::unique_ptr<SysData> const& sysData) = 0;
		};
	}
}


#endif