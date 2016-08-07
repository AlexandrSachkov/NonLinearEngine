#ifndef NL_TASK_H_
#define NL_TASK_H_

#include "tbb\task.h"
#include <functional>

namespace NLE
{
	namespace TASK
	{
		class ITaskScheduler;
		class Task : public tbb::task
		{
		public:
			Task(ITaskScheduler* const scheduler, std::function<void()> const& operation);
			~Task();

			tbb::task* execute();

		private:
			std::function<void()> _operation;
			ITaskScheduler* const _scheduler;
		};
	}
}


#endif