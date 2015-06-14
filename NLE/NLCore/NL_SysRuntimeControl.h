#ifndef NL_SYS_RUNTIME_CONTROL_H_
#define NL_SYS_RUNTIME_CONTROL_H_

#include "NL_Scheduler.h"
#include "NL_SysManager.h"

namespace NLE
{
	namespace Core
	{
		class SysRuntimeControl
		{
		public:
			SysRuntimeControl(
				std::unique_ptr<Scheduler> const& scheduler,
				std::unique_ptr<SysManager> const& sysManager) 
				:
				_scheduler(scheduler),
				_sysManager(sysManager)
			{
			}

			~SysRuntimeControl()
			{
			}

			void startSystem(uint_fast8_t sysId)
			{
				_scheduler->requestExecution(sysId);
			}

			uint_fast8_t getNumHardwareThreads()
			{
				return _scheduler->getNumHardwareThreads();
			}

			uint_fast8_t getNumSystems()
			{
				return _sysManager->getNumSystems();
			}

		private:
			std::unique_ptr<Scheduler> const& _scheduler;
			std::unique_ptr<SysManager> const& _sysManager;
		};
	}
}

#endif