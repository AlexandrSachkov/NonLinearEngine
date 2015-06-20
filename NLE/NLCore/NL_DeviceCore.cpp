#include "NL_DeviceCore.h"

#include "NL_Clock.h"
#include "NL_System.h"
#include "NL_SysManager.h"
#include "NL_Scheduler.h"
#include "NL_StateManager.h"
#include "NL_IEngine.h"

#include <cassert>

namespace NLE 
{
	namespace Core 
	{
		DeviceCore *DeviceCore::_deviceCore = nullptr;

		DeviceCore::DeviceCore()
		{ 
			_clock = std::make_unique<Clock>();
			_sysManager = std::make_unique<SysManager>();
			_scheduler = std::make_unique<Scheduler>();
			_stateManager = std::make_unique<StateManager>();
			_iEngine = std::make_unique<IEngine>(_scheduler, _sysManager, _stateManager);
		}

		DeviceCore::~DeviceCore()
		{
			release();
		}

		bool DeviceCore::initialize()
		{
			std::unique_ptr<Scheduler>& scheduler = _scheduler;
			std::unique_ptr<SysManager>& sysMngr = _sysManager;
			std::unique_ptr<StateManager>& stateMngr = _stateManager;

			if (!_clock->initialize([&scheduler, &sysMngr, &stateMngr](){
				printf("Tick...\n");
				scheduler->manageExecution(sysMngr, stateMngr);
			}))
				return false;
				
			if (!_scheduler->initialize())
				return false;
			if (!_sysManager->initialize(_scheduler, _iEngine))
				return false;
			if (!_stateManager->initialize())
				return false;
			
			return true;
		}

		void DeviceCore::release()
		{		
			if (_sysManager)
				_sysManager->release();
			if (_stateManager)
				_stateManager->release();
			if (_scheduler)
				_scheduler->release();
			if (_clock)
				_clock->release();
		}

		void DeviceCore::attachSystem(ExecutionDesc executionDesc, std::unique_ptr<System> system)
		{
			_sysManager->attachSystem(executionDesc, std::move(system));
		}

		void DeviceCore::setClockPeriodNs(unsigned long long periodNs)
		{
			_clock->setPeriodNs(periodNs);
		}

		uint_fast32_t DeviceCore::getNumHardwareThreads()
		{
			return _scheduler->getNumHardwareThreads();
		}

		void DeviceCore::run()
		{
			_clock->run();
		}

		void DeviceCore::stop()
		{
			_clock->stop();
		}
	}
}