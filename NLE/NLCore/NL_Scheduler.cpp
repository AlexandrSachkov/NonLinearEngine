#include "NL_Scheduler.h"
#include "NL_SysManager.h"
#include "tbb/tbb.h"
#include "NL_System.h"
#include "NL_SysTask.h"

namespace NLE
{
	namespace Core
	{
		Scheduler::Scheduler() :
			_scheduledSystems(),
			_numThreads()
		{

		}

		Scheduler::~Scheduler()
		{

		}

		bool Scheduler::initialize()
		{
			_numThreads = tbb::task_scheduler_init::default_num_threads();
			tbb::task_scheduler_init init(_numThreads);
			printf("Running on %i threads.\n", _numThreads);
			return true;
		}

		void Scheduler::release()
		{

		}

		uint_fast8_t Scheduler::getNumThreads()
		{
			return _numThreads;
		}

		void Scheduler::scheduleExecution(uint_fast8_t sysId)
		{
			_scheduledSystems.push(sysId);
		}

		void Scheduler::executeSystems(std::unique_ptr<SysManager> const& sysManager)
		{
			uint_fast8_t sysId;
			while (_scheduledSystems.try_pop(sysId))
			{
				NLE::Core::SysTask& task = *sysManager->getSystemById(sysId).get()->getTask(this);
				tbb::task::enqueue(task);
			}
		}
	}
}