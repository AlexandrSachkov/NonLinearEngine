#ifndef NL_SYS_TASK_H_
#define NL_SYS_TASK_H_

#include "NL_Scheduler.h"
#include "tbb\task.h"
#include <functional>

namespace NLE
{
	namespace Core
	{
		class SysTask : public tbb::task
		{

		public:
			SysTask(Scheduler* scheduler, std::function<tbb::task*()> operation)
			{
				_scheduler = scheduler;
				_operation = operation;
			}

			tbb::task* execute()
			{
				tbb::task* task = _operation();
				return task;
			}

		private:
			Scheduler* _scheduler;
			std::function<tbb::task*()> _operation;
		};
	}
}

#endif