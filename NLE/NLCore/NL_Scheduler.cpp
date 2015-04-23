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
			_syncSystems(),
			_asyncSystems(),
			_numCores()
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

		void Scheduler::scheduleExecution(ExecutionDesc execDesc)
		{
			printf("Scheduling system %i\n", execDesc.getSysId());
			if (execDesc.getExecutionType() == ExecutionType::SYNC)
				_syncSystems.push(execDesc);
			else 
				_asyncSystems.push(execDesc);
		}

		void Scheduler::executeSystems(
			std::unique_ptr<SysManager> const& sysManager,
			std::unique_ptr<StateManager> const& stateManager)
		{
			ExecutionDesc execDesc;
			std::function<void()> procedure;

			size_t  size = _syncSystems.size();
			if (size > 0 && size == sysManager->getNumSyncSystems())
			{
				while (_syncSystems.try_pop(execDesc))
				{
					procedure = sysManager->getSystemById(execDesc.getSysId()).get()->getExecutionProcedure();
					tbb::task::enqueue(*new (tbb::task::allocate_root())NLE::Core::SysTask(this, execDesc, procedure));
				}
				stateManager->distributeData();
			}

			if (!_asyncSystems.empty())
			{
				while (_asyncSystems.try_pop(execDesc))
				{
					procedure = sysManager->getSystemById(execDesc.getSysId()).get()->getExecutionProcedure();
					tbb::task::enqueue(*new (tbb::task::allocate_root())NLE::Core::SysTask(this, execDesc, procedure));
				}
			}
		}
	}
}