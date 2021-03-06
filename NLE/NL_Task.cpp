#include "NL_Task.h"
#include "NL_ITaskScheduler.h"

namespace NLE
{
	namespace TASK
	{
		Task::Task(ITaskScheduler* const scheduler, std::function<void()> const& operation) :
			_scheduler(scheduler),
			_operation(operation)
		{
		}

		Task::~Task()
		{
		}

		tbb::task* Task::execute()
		{
			_operation();
			_scheduler->notifyOfCompletion();
			return nullptr;
		}
	}
}