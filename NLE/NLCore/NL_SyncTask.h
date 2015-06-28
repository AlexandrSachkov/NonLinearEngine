#ifndef NL_SYNC_TASK_H_
#define NL_SYNC_TASK_H_

#include "NL_Scheduler.h"
#include <functional>

namespace NLE
{
	namespace Core
	{
		class SyncTask
		{

		public:
			SyncTask(Scheduler& scheduler, uint_fast32_t sysId, std::function<void()> const& operation) :
				_scheduler(scheduler),
				_sysId(sysId),
				_operation(operation)
			{
			}

			~SyncTask()
			{
			}

			void execute()
			{
				_operation();
				_scheduler.signalFinished(_sysId);
			}

		private:
			Scheduler& _scheduler;
			uint_fast32_t _sysId;
			std::function<void()> _operation;
		};
	}
}

#endif