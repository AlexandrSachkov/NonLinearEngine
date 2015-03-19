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
			SysTask(std::function<tbb::task*()> operation)
			{
				_operation = operation;
			}

			tbb::task* execute()
			{
				return _operation();
			}

		private:
			std::function<tbb::task*()> _operation;
		};
	}
}

#endif