#ifndef NL_SYS_TASK_H_
#define NL_SYS_TASK_H_

#include "NL_Scheduler.h"
#include "NL_Task.h"

#include <functional>

namespace NLE
{
	namespace Core
	{
		class SysTask : public Task
		{

		public:
			SysTask(Scheduler& scheduler, uint_fast32_t sysId, std::function<void()> const& operation) :
				Task(operation),
				_scheduler(scheduler),
				_sysId(sysId)
			{
			}

			~SysTask()
			{
			}

			tbb::task* execute()
			{
				Task::execute();
				_scheduler.signalFinished(_sysId);
				return nullptr;
			}

		private:
			Scheduler& _scheduler;
			uint_fast32_t _sysId;
		};
	}
}

#endif