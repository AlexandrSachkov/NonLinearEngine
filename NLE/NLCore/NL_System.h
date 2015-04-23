#ifndef NL_SYSTEM_H_
#define NL_SYSTEM_H_

#include <cstdint>
#include <memory>
#include "NL_Scheduler.h"

namespace NLE 
{
	namespace Core 
	{
		class SysTask;
		class Scheduler;
		class SysState;
		class StateManager;

		class System
		{
		public:
			virtual ~System(){}

			virtual bool initialize(
				uint_fast8_t id,
				std::unique_ptr<StateManager> const& stateManager) = 0;
			virtual void release() = 0;

			virtual ExecutionDesc getExecutionDesc() = 0;
			virtual uint_fast8_t getID() = 0;

			virtual SysTask* getTask(
				std::unique_ptr<Scheduler> const& scheduler) = 0;	
		};		
	}
}

#endif