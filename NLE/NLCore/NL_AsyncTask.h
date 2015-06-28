#ifndef NL_ASYNC_TASK_H_
#define NL_ASYNC_TASK_H_

#include "NL_Scheduler.h"
#include "tbb\task.h"
#include <functional>

namespace NLE
{
	namespace Core
	{
		class AsyncTask : public tbb::task
		{

		public:
			AsyncTask(Scheduler& scheduler, uint_fast32_t sysId, std::function<void()> const& operation) :
				_scheduler(scheduler),
				_sysId(sysId),
				_operation(operation)
			{
			}

			~AsyncTask()
			{
			}

			tbb::task* execute()
			{
				_operation();
				_scheduler.signalFinished(_sysId);
				return nullptr;
			}

		private:
			Scheduler& _scheduler;
			uint_fast32_t _sysId;
			std::function<void()> _operation;
		};
	}
}

#endif