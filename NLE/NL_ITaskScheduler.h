#ifndef NL_I_TASK_SCHEDULER_H_
#define NL_I_TASK_SCHEDULER_H_

#include "tbb/task.h"
#include <functional>

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

		class ITaskScheduler
		{
		public:
			virtual void queueProcedure(std::function<void()> procedure, TaskPriority priority) = 0;
		};
	}
}

#endif