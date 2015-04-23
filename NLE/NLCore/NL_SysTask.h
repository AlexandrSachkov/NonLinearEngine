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
			SysTask(Scheduler* scheduler, ExecutionDesc execDesc, std::function<void()> operation) :
				_scheduler(scheduler),
				_execDesc(execDesc),
				_operation(operation)
			{
			}

			tbb::task* execute()
			{
				_operation();
				_scheduler->scheduleExecution(_execDesc);
				return nullptr;
			}

		private:
			Scheduler* _scheduler;
			ExecutionDesc _execDesc;
			std::function<void()> _operation;
		};
	}
}

#endif