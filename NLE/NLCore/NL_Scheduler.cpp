#include "NL_Scheduler.h"
#include "NL_SysManager.h"
#include "tbb/tbb.h"
#include "NL_Clock.h"
#include "NL_System.h"
#include "NL_AsyncTask.h"
#include "NL_SyncTask.h"
#include "NL_StateManager.h"

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
		}

		Scheduler::~Scheduler()
		{

		}

		bool Scheduler::initialize()
		{
			assert(!_initialized);

			uint_fast32_t _numHardwareThreads = getNumThreads();
			_taskSchedulerInit = new tbb::task_scheduler_init(_numHardwareThreads + 1);
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

		void Scheduler::signalFinished(uint_fast32_t sysId)
		{
			_finished.push(sysId);
		}

		void Scheduler::requestExecution(uint_fast32_t sysId)
		{
			_toSchedule.push(sysId);
		}

		void Scheduler::manageExecution(
			std::unique_ptr<SysManager> const& sysManager,
			std::unique_ptr<StateManager> const& stateManager)
		{
			stateManager->processRequests();

			uint_fast32_t sysId;
			ExecutionDesc* execDesc;

			if (!_finished.empty())
			{
				while (_finished.try_pop(sysId))
				{
					stateManager->distributeFrom(sysId);
					execDesc = &sysManager->getExecutionDesc(sysId);
					if (execDesc->getExecution() == Execution::RECURRING)
					{
						_scheduledSystems.add(sysId);
					}				
				}
			}

			if (!_toSchedule.empty())
			{
				while (_toSchedule.try_pop(sysId))
				{
					_scheduledSystems.add(sysId);
				}
			}
	
			for (uint_fast32_t i = 0; i < _scheduledSystems.size(); ++i)
			{
				sysId = _scheduledSystems[i];
				execDesc = &sysManager->getExecutionDesc(sysId);

				if (execDesc->isTimeToStart())
				{
					stateManager->distributeTo(sysId);

					if (execDesc->getMode() == Mode::ASYNC)
					{
						execDesc->resetStartTime();
						
						std::function<void()> const& procedure = sysManager->getSystem(sysId)->getExecutionProcedure();
						AsyncTask* task = new (tbb::task::allocate_root())NLE::Core::AsyncTask(*this, sysId, procedure);
						switch (execDesc->getPriority())
						{
						case Priority::LOW:
							tbb::task::enqueue(*task, tbb::priority_low);
							break;
						case Priority::STANDARD:
							tbb::task::enqueue(*task, tbb::priority_normal);
							break;
						case Priority::HIGH:
							tbb::task::enqueue(*task, tbb::priority_high);
							break;
						default:
							//should never be reached
							assert(false);
						}

					} else {
						_syncSystemsToRun.push_back(sysId);
					}
				
					_scheduledSystems.itRemove(i);
				}
			}

			if (_syncSystemsToRun.size() > 0)
			{
				for (uint_fast32_t sysId : _syncSystemsToRun)
				{
					execDesc = &sysManager->getExecutionDesc(sysId);
					execDesc->resetStartTime();

					std::function<void()> const& procedure = sysManager->getSystem(sysId)->getExecutionProcedure();
					SyncTask task(*this, sysId, procedure);
					task.execute();
				}
				_syncSystemsToRun.clear();
			}
		}
	}
}