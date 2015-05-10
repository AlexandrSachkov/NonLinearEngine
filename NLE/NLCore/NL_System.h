#ifndef NL_SYSTEM_H_
#define NL_SYSTEM_H_

#include <cstdint>
#include <memory>
#include <functional>


namespace NLE 
{
	namespace Core 
	{
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
			virtual std::function<void()> getExecutionProcedure() = 0;	
		};		
	}
}

#endif