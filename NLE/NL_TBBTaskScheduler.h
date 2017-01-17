#pragma once

#include "NL_Task.h"
#include "NL_ITaskScheduler.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/concurrent_queue.h"
#include "tbb/atomic.h"
#include <functional>

namespace NLE
{
	namespace TASK
	{
		class TBBTaskScheduler : public ITaskScheduler
		{
		public:
			TBBTaskScheduler();
			TBBTaskScheduler(unsigned int numThreads);
			~TBBTaskScheduler();

			void queueProcedure(std::function<void()> procedure, TaskPriority priority);
			void dispatchTasks();
			void notifyOfCompletion();
			void waitOnTasks();
			unsigned int getNumThreads();

		private:
			void runProcedure(std::function<void()>& procedure, TaskPriority priority);

			tbb::task_scheduler_init _scheduler;
			const unsigned int _numThreads;
			tbb::concurrent_queue<std::pair<std::function<void()>, TaskPriority>> _tasks;
			tbb::atomic<unsigned int> _runningTasks;
		};
	}

}

