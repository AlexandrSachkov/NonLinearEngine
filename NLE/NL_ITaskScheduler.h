#pragma once

#include "tbb/task.h"
#include <functional>
#include <memory>

namespace NLE
{
	namespace TASK
	{
		enum TaskPriority
		{
			STANDARD = tbb::priority_normal,
			HIGH = tbb::priority_high,
			LOW = tbb::priority_low
		};

		class ITaskScheduler_EService
		{
		public:
			virtual void queueProcedure(std::function<void()> procedure, TaskPriority priority) = 0;
			virtual unsigned int getNumThreads() = 0;
		};

		class ITaskScheduler : public ITaskScheduler_EService
		{
		public:
			virtual void dispatchTasks() = 0;
			virtual void notifyOfCompletion() = 0;
			virtual void waitOnTasks() = 0;
		};

		typedef std::shared_ptr<ITaskScheduler> ITaskSchedulerSP;
		typedef std::shared_ptr<ITaskScheduler_EService> ITaskScheduler_EServiceSP;
	}
}