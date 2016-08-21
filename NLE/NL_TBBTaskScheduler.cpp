#include "NL_TbbTaskScheduler.h"

namespace NLE
{
	namespace TASK
	{
		TBBTaskScheduler::TBBTaskScheduler() :
			_scheduler(tbb::task_scheduler_init::default_num_threads()),
			_numThreads(tbb::task_scheduler_init::default_num_threads())
		{
			_runningTasks.store(0);
		}

		TBBTaskScheduler::TBBTaskScheduler(unsigned int numThreads) :
			_scheduler(numThreads),
			_numThreads(numThreads)
		{
			_runningTasks.store(0);
		}

		TBBTaskScheduler::~TBBTaskScheduler()
		{
		}

		void TBBTaskScheduler::queueProcedure(std::function<void()> procedure, TaskPriority priority)
		{
			_tasks.push({ procedure, priority });
		}

		void TBBTaskScheduler::dispatchTasks()
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

		void TBBTaskScheduler::runProcedure(std::function<void()>& procedure, TaskPriority priority)
		{
			Task* task = new (tbb::task::allocate_root())Task(this, procedure);
			tbb::task::enqueue(*task, (tbb::priority_t)priority);
		}

		void TBBTaskScheduler::notifyOfCompletion()
		{
			_runningTasks.fetch_and_decrement();
		}

		void TBBTaskScheduler::waitOnTasks()
		{
			while (_runningTasks != 0)
			{
			}
		}

		unsigned int TBBTaskScheduler::getNumThreads()
		{
			return _numThreads;
		}
	}

}