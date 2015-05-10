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
			SysTask(Scheduler* scheduler, uint_fast8_t sysId, std::function<void()> operation) :
				_scheduler(scheduler),
				_sysId(sysId),
				_operation(operation)
			{
			}

			~SysTask()
			{
			}

			tbb::task* execute()
			{
				_operation();
				_scheduler->signalFinished(_sysId);
				return nullptr;
			}

		private:
			Scheduler* _scheduler;
			uint_fast8_t _sysId;
			std::function<void()> _operation;
		};
	}
}

#endif