#ifndef NL_SCHEDULER_H_
#define NL_SCHEDULER_H_

#include "NL_ExecutionDesc.h"
#include "NL_PContainer.h"
#include "tbb\concurrent_queue.h"
#include "tbb/task_scheduler_init.h"
#include "tbb\scalable_allocator.h"

namespace NLE 
{
	namespace Core 
	{
		class SysManager;
		class StateManager;
		class SysTask;
		class Clock;

		class Scheduler 
		{
		public:
			Scheduler();
			~Scheduler();

			bool initialize();
			void release();

			uint_fast32_t getNumHardwareThreads();
			void requestExecution(uint_fast32_t sysId);
			void signalFinished(uint_fast32_t sysId);
			void manageExecution(
				std::unique_ptr<SysManager> const& sysManager,
				std::unique_ptr<StateManager> const& stateManager);

		private:
			tbb::task_scheduler_init* _taskSchedulerInit;		
			tbb::concurrent_queue<uint_fast32_t> _toSchedule;
			tbb::concurrent_queue<uint_fast32_t> _finished;
		
			Data::PContainer<uint_fast32_t> _scheduledSystems;
		};
	}
}

#endif