#include "NL_TaskScheduler.h"

namespace NLE
{
	namespace TASK
	{
		TaskScheduler::TaskScheduler() :
			_scheduler(tbb::task_scheduler_init::default_num_threads())
		{
			_runningTasks.store(0);
		}

		TaskScheduler::TaskScheduler(unsigned int numThreads) :
			_scheduler(numThreads)
		{
			_runningTasks.store(0);
		}

		TaskScheduler::~TaskScheduler()
		{
		}

		void TaskScheduler::queueProcedure(std::function<void()> procedure, TaskPriority priority)
		{
			_tasks.push({ procedure, priority });
		}

		void TaskScheduler::dispatchTasks()
		{
			if (!_tasks.empty())
			{
				std::pair<std::function<void()>, TaskPriority> procedure;
				while (_tasks.try_pop(procedure))
				{
					runProcedure(procedure.first, procedure.second);
					_runningTasks.fetch_and_increment();
				}
			}
		}

		void TaskScheduler::runProcedure(std::function<void()>& procedure, TaskPriority priority)
		{
			Task* task = new (tbb::task::allocate_root())Task(this, procedure);
			tbb::task::enqueue(*task, (tbb::priority_t)priority);
		}

		void TaskScheduler::notifyOfCompletion()
		{
			_runningTasks.fetch_and_decrement();
		}

		void TaskScheduler::waitOnTasks()
		{
			while (_runningTasks != 0)
			{
			}
		}
	}

}