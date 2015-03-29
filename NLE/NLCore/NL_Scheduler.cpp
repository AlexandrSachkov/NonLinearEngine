#include "NL_Scheduler.h"
#include "NL_SysManager.h"
#include "tbb/tbb.h"
#include "NL_System.h"
#include "NL_SysTask.h"
#include "NL_DataManager.h"

namespace NLE
{
	namespace Core
	{
		Scheduler::Scheduler() :
			_scheduledSystems(),
			_numThreads(),
			_scheduler(this)
		{
		}

		Scheduler::~Scheduler()
		{

		}

		bool Scheduler::initialize()
		{
			_numThreads = tbb::task_scheduler_init::default_num_threads() + 1;
			_taskSchedulerInit = new tbb::task_scheduler_init(_numThreads);
			printf("Running on %i threads.\n", _numThreads);
			return true;
		}

		void Scheduler::release()
		{
			if (_taskSchedulerInit)
				delete _taskSchedulerInit;
		}

		uint_fast8_t Scheduler::getNumThreads()
		{
			return _numThreads;
		}

		void Scheduler::scheduleExecution(uint_fast8_t sysId)
		{
			_scheduledSystems.push(sysId);
		}

		void Scheduler::executeSystems(
			std::unique_ptr<SysManager> const& sysManager, 
			std::unique_ptr<DataManager> const& dataManager)
		{
			uint_fast8_t sysId;		

			while (_scheduledSystems.try_pop(sysId))
			{
				NLE::Core::SysTask& task = *sysManager->getSystemById(sysId).get()->getTask(
					_scheduler,
					dataManager->getDataHandle(sysId));
				tbb::task::enqueue(task);
			}
		}
	}
}