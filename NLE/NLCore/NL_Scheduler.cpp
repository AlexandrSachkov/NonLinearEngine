#include "NL_Scheduler.h"
#include "NL_SysManager.h"
#include "tbb/tbb.h"
#include "NL_System.h"
#include "NL_SysTask.h"
#include "NL_StateManager.h"

namespace NLE
{
	namespace Core
	{
		Scheduler::Scheduler() :
			_scheduledSystems(),
			_numCores(),
			_scheduler(this)
		{
		}

		Scheduler::~Scheduler()
		{

		}

		bool Scheduler::initialize()
		{
			_numCores = tbb::task_scheduler_init::default_num_threads();
			_taskSchedulerInit = new tbb::task_scheduler_init(_numCores + 1);
			printf("Running on %i threads.\n", _numCores + 1);
			return true;
		}

		void Scheduler::release()
		{
			if (_taskSchedulerInit)
				delete _taskSchedulerInit;
		}

		uint_fast8_t Scheduler::getNumCores()
		{
			return _numCores;
		}

		void Scheduler::scheduleExecution(uint_fast8_t sysId)
		{
			_scheduledSystems.push(sysId);
		}

		void Scheduler::executeSystems(
			std::unique_ptr<SysManager> const& sysManager, 
			std::unique_ptr<StateManager> const& stateManager)
		{
			uint_fast8_t sysId;		

			while (_scheduledSystems.try_pop(sysId))
			{
				NLE::Core::SysTask& task = *sysManager->getSystemById(sysId).get()->getTask(
					_scheduler,
					stateManager->getDataHandle(sysId));
				tbb::task::enqueue(task);
			}
		}
	}
}