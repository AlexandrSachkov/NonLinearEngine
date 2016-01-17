#ifndef NL_SCHEDULER_H_
#define NL_SCHEDULER_H_

#include "NL_ExecutionDesc.h"
#include "NL_PContainer.h"
#include "NL_Task.h"

#include "tbb\concurrent_queue.h"
#include "tbb/task_scheduler_init.h"
#include "tbb\scalable_allocator.h"
#include "tbb/atomic.h"
#include <unordered_map>


#include <functional>

namespace NLE 
{
	namespace Core 
	{
		class SysManager;
		class StateManager;
		class Clock;
		class System;

		class Scheduler 
		{
		public:
			Scheduler();
			~Scheduler();

			bool initialize(uint_fast32_t numAllocatedThreads);
			void release();

			void setNumThreads(uint_fast32_t numThreads);
			uint_fast32_t getNumThreads();
			void scheduleExecution(uint_fast32_t sysId);

			void signalFinished(uint_fast32_t sysId);
			void manageExecution(
				std::unordered_map<uint_fast32_t, std::unique_ptr<System>>& systems,
				std::unordered_map<uint_fast32_t, ExecutionDesc>& executionDesc);
			int_fast32_t getNumRunningTasks();

			void runAsync(std::function<void()>& operation, Priority priority);

		private:
			void runTask(Task& task, Priority priority);

			tbb::task_scheduler_init* _taskSchedulerInit;		
			tbb::concurrent_queue<uint_fast32_t> _starting;
			tbb::concurrent_queue<uint_fast32_t> _finished;
			tbb::concurrent_queue <std::pair<std::function<void()>, Priority>> _asyncOps;
		
			Data::PContainer<uint_fast32_t> _scheduledSystems;
			std::vector<uint_fast32_t, tbb::scalable_allocator<uint_fast32_t>> _syncSystemsToRun;
			uint_fast32_t _numThreads;
			bool _initialized;
			tbb::atomic<int_fast32_t> _numRunningTasks;
		};
	}
}

#endif