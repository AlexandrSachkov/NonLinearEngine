#ifndef NL_TASK_H_
#define NL_TASK_H_

#include "tbb\task.h"
#include <functional>

namespace NLE
{
	namespace TASK
	{
		class TaskScheduler;
		class Task : public tbb::task
		{
		public:
			Task(TaskScheduler* const scheduler, std::function<void()> const& operation);
			~Task();

			tbb::task* execute();

		private:
			std::function<void()> _operation;
			TaskScheduler* const _scheduler;
		};
	}
}


#endif