#include "NL_Scheduler.h"
#include "tbb/tbb.h"
#include "NL_System.h"
#include "NL_SysTask.h"

#include <assert.h>

namespace NLE
{
	namespace Core
	{
		Scheduler::Scheduler() :
			_scheduledSystems(10),
			_initialized(false)
		{
			_numThreads = tbb::task_scheduler_init::default_num_threads();
			_numRunningTasks.fetch_and_store(0);
		}

		Scheduler::~Scheduler()
		{

		}

		bool Scheduler::initialize(uint_fast32_t numAllocatedThreads)
		{
			assert(!_initialized);
			_numThreads -= numAllocatedThreads + 1;
			_taskSchedulerInit = new tbb::task_scheduler_init(_numThreads);
			_initialized = true;	
			return true;
		}

		void Scheduler::release()
		{
			if (_taskSchedulerInit)
				delete _taskSchedulerInit;
			_initialized = false;
		}

		void Scheduler::setNumThreads(uint_fast32_t numThreads)
		{
			assert(!_initialized && numThreads > 0);
			_numThreads = numThreads;
		}

		uint_fast32_t Scheduler::getNumThreads()
		{
			return _numThreads;
		}

		int_fast32_t Scheduler::getNumRunningTasks()
		{
			return _numRunningTasks.load();
		}

		void Scheduler::signalFinished(uint_fast32_t sysId)
		{
			_finished.push(sysId);
			_numRunningTasks.fetch_and_decrement();
		}

		void Scheduler::scheduleExecution(uint_fast32_t sysId)
		{
			_starting.push(sysId);
		}

		void Scheduler::manageExecution(
			std::unordered_map<uint_fast32_t, std::unique_ptr<System>>& systems,
			std::unordered_map<uint_fast32_t, ExecutionDesc>& executionDesc)
		{
			uint_fast32_t sysId;
			ExecutionDesc* execDesc;

			if (!_finished.empty())
			{
				while (_finished.try_pop(sysId))
				{
					execDesc = &executionDesc.at(sysId);
					if (execDesc->enabled())
					{
						if (execDesc->getExecution() == Execution::RECURRING)
						{
							_scheduledSystems.add(sysId);
						}
					}
					else
					{
						systems.at(sysId)->stop();
						execDesc->setState(State::STOPPED);
					}
				}
			}

			if (!_starting.empty())
			{
				while (_starting.try_pop(sysId))
				{
					execDesc = &executionDesc.at(sysId);
					_scheduledSystems.add(sysId);			
				}
			}
	
			for (uint_fast32_t i = 0; i < _scheduledSystems.size(); ++i)
			{
				sysId = _scheduledSystems[i];
				execDesc = &executionDesc.at(sysId);

				if (execDesc->isTimeToStart())
				{
					_numRunningTasks.fetch_and_increment();

					if (execDesc->getMode() == Mode::ASYNC)
					{
						execDesc->resetStartTime();
						
						std::function<void()> const& procedure = systems.at(sysId)->getExecutionProcedure();
						SysTask* task = new (tbb::task::allocate_root())NLE::Core::SysTask(*this, sysId, procedure);
						runTask(*task, execDesc->getPriority());
						
					} else {
						_syncSystemsToRun.push_back(sysId);
					}
				
					_scheduledSystems.itRemove(i);
				}
			}

			std::pair<std::function<void()>, Priority> asyncOp;
			while (_asyncOps.try_pop(asyncOp))
			{
				Task* task = new (tbb::task::allocate_root())NLE::Core::Task(asyncOp.first);
				runTask(*task, asyncOp.second);
			}


			if (_syncSystemsToRun.size() > 0)
			{
				for (uint_fast32_t sysId : _syncSystemsToRun)
				{
					execDesc = &executionDesc.at(sysId);
					execDesc->resetStartTime();

					std::function<void()> const& procedure = systems.at(sysId)->getExecutionProcedure();
					SysTask task(*this, sysId, procedure);
					task.execute();
				}
				_syncSystemsToRun.clear();
			}
		}


		void Scheduler::runTask(Task& task, Priority priority)
		{
			switch (priority)
			{
			case Priority::LOW:
				tbb::task::enqueue(task, tbb::priority_low);
				break;
			case Priority::STANDARD:
				tbb::task::enqueue(task, tbb::priority_normal);
				break;
			case Priority::HIGH:
				tbb::task::enqueue(task, tbb::priority_high);
				break;
			default:
				//should never be reached
				assert(false);
			}
		}

		void Scheduler::runAsync(std::function<void()>& operation, Priority priority)
		{
			_asyncOps.push(std::make_pair<>(operation, priority));
		}
	}
}