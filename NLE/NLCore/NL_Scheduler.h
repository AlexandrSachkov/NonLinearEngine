#ifndef NL_SCHEDULER_H_
#define NL_SCHEDULER_H_

#include "NL_ExecutionDesc.h"

#include "tbb/concurrent_priority_queue.h"
#include "tbb/task_scheduler_init.h"


namespace NLE 
{
	namespace Core 
	{
		class SysManager;
		class StateManager;

		class PriorityComparator
		{
		public:
			bool operator() (const ExecutionDesc& firstDesc, const ExecutionDesc& secondDesc)
			{
				return secondDesc.getPriority() < firstDesc.getPriority();
			}
		};

		class Scheduler 
		{
		public:
			Scheduler();
			~Scheduler();

			bool initialize();
			void release();

			uint_fast8_t getNumCores();
			void scheduleExecution(ExecutionDesc execDesc);
			void executeSystems(
				std::unique_ptr<SysManager> const& sysManager,
				std::unique_ptr<StateManager> const& stateManager);

		private:
			tbb::task_scheduler_init* _taskSchedulerInit;		
			tbb::concurrent_priority_queue<ExecutionDesc, PriorityComparator> _systems;
			uint_fast8_t _numCores;
		};
	}
}

#endif