#ifndef NL_SCHEDULER_H_
#define NL_SCHEDULER_H_

#include "tbb/concurrent_priority_queue.h"
#include "tbb/task_scheduler_init.h"

namespace NLE 
{
	namespace Core 
	{
		class SysManager;
		class StateManager;

		enum ExecutionType { SYNC, ASYNC };
		enum Priority { LOW, STANDARD, HIGH };

		//====================================================================================
		class ExecutionDesc
		{
		public:
			//Only used when popping from queue
			ExecutionDesc() :
				_execType(ExecutionType::SYNC),
				_priority(Priority::LOW),
				_sysId(-1)
			{
			}

			ExecutionDesc(ExecutionType execType, Priority priority, uint_fast8_t sysId) :
				_execType(execType),
				_priority(priority),
				_sysId(sysId)
			{
			}

			~ExecutionDesc()
			{
			}

			ExecutionType getExecutionType() const
			{
				return _execType;
			}

			Priority getPriority() const
			{
				return _priority;
			}

			uint_fast8_t getSysId() const
			{
				return _sysId;
			}

		private:
			ExecutionType _execType;
			Priority _priority;
			uint_fast8_t _sysId;
		};

		//====================================================================================

		class PriorityComparator
		{
		public:
			bool operator() (const ExecutionDesc& firstDesc, const ExecutionDesc& secondDesc)
			{
				return firstDesc.getPriority() < secondDesc.getPriority();
			}
		};

		//====================================================================================

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
			
			tbb::concurrent_priority_queue<ExecutionDesc, PriorityComparator> _asyncSystems;
			tbb::concurrent_priority_queue<ExecutionDesc, PriorityComparator> _syncSystems;

			uint_fast8_t _numCores;
		};
	}
}

#endif