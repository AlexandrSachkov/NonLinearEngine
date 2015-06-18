#ifndef NL_I_ENGINE_H_
#define NL_I_ENGINE_H_

#include "NL_Scheduler.h"
#include "NL_SysManager.h"
#include "NL_StateManager.h"

namespace NLE
{
	namespace Core
	{
		class IEngine
		{
		public:
			IEngine(
				std::unique_ptr<Scheduler> const& scheduler,
				std::unique_ptr<SysManager> const& sysManager,
				std::unique_ptr<StateManager> const& stateManager) 
				:
				_scheduler(scheduler),
				_sysManager(sysManager),
				_stateManager(stateManager)
			{
			}

			~IEngine()
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

			template <typename T>
			Data::SDistributor<T>& getSDistributor(unsigned int id)
			{
				return _stateManager->getSDistributor<T>(id);
			}

			template <typename T>
			Data::MSDistributor<T>& getMSDistributor(unsigned int id)
			{
				return _stateManager->getMSDistributor<T>(id);
			}

		private:
			std::unique_ptr<Scheduler> const& _scheduler;
			std::unique_ptr<SysManager> const& _sysManager;
			std::unique_ptr<StateManager> const& _stateManager;
		};
	}
}

#endif