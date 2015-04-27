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
		Scheduler::Scheduler()
		{
		}

		Scheduler::~Scheduler()
		{

		}

		bool Scheduler::initialize()
		{
			_numHardwareThreads = tbb::task_scheduler_init::default_num_threads();
			_taskSchedulerInit = new tbb::task_scheduler_init(_numHardwareThreads + 1);
			printf("Running on %i threads.\n", _numHardwareThreads + 1);
			return true;
		}

		void Scheduler::release()
		{
			if (_taskSchedulerInit)
				delete _taskSchedulerInit;
		}

		uint_fast8_t Scheduler::getNumHardwareThreads()
		{
			return _numHardwareThreads;
		}

		void Scheduler::scheduleExecution(ExecutionDesc execDesc)
		{
			printf("Scheduling system %i\n", execDesc.getSysId());
			_systems.push(execDesc);
		}

		void Scheduler::executeSystems(
			std::unique_ptr<SysManager> const& sysManager,
			std::unique_ptr<StateManager> const& stateManager)
		{
			if (!_systems.empty())
			{
				stateManager->processRequests();

				ExecutionDesc execDesc;				
				while (_systems.try_pop(execDesc))
				{
					_execDescriptions.push_back(execDesc);			
				}
				
				for (uint_fast32_t i = 0; i < _execDescriptions.size(); ++i)
				{
					stateManager->distributeFrom(_execDescriptions[i].getSysId());
				}

				for (uint_fast32_t i = 0; i < _execDescriptions.size(); ++i)
				{
					stateManager->distributeTo(_execDescriptions[i].getSysId());
				}

				std::function<void()> procedure;
				for (uint_fast32_t i = 0; i < _execDescriptions.size(); ++i)
				{
					procedure = sysManager->getSystemById(_execDescriptions[i].getSysId()).get()->getExecutionProcedure();
					tbb::task::enqueue(*new (tbb::task::allocate_root())NLE::Core::SysTask(this, _execDescriptions[i], procedure));
				}	
				_execDescriptions.clear();
			}
		}
	}
}