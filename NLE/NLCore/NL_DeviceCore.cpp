#include "NL_DeviceCore.h"

#include "NL_Clock.h"
#include "NL_System.h"
#include "NL_SysManager.h"
#include "NL_Scheduler.h"
#include "NL_StateManager.h"
#include "NL_IEngine.h"
#include "NL_ExecutionDesc.h"

#include <cassert>

namespace NLE 
{
	namespace Core 
	{
		DeviceCore* DeviceCore::_deviceCore = nullptr;

		DeviceCore::DeviceCore() :
			_initialized(false)
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
			assert(!_initialized);

			if (!_clock->initialize([&](){
				if (_uiOperation)
				{
					_uiOperation();
				}
				_scheduler->manageExecution(_sysManager, _stateManager);
			}))
				return false;
				
			if (!_scheduler->initialize())
				return false;
			if (!_sysManager->initialize(_scheduler, _iEngine))
				return false;
			if (!_stateManager->initialize())
				return false;
			
			_initialized = true;
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

			_initialized = false;
		}

		void DeviceCore::attachUITheadOperation(unsigned long long periodNs, std::function<void()> uiOperation)
		{
			assert(!_initialized);
			_uiOperation = uiOperation;
		}

		void DeviceCore::attachSystem(uint_fast32_t sysId, ExecutionDesc& executionDesc, std::unique_ptr<System> system)
		{
			_sysManager->attachSystem(sysId, executionDesc, std::move(system));
		}

		void DeviceCore::setClockPeriodNs(unsigned long long periodNs)
		{
			_clock->setPeriodNs(periodNs);
		}

		void DeviceCore::setNumThreads(uint_fast32_t numThreads)
		{
			_scheduler->setNumThreads(numThreads);
		}

		uint_fast32_t DeviceCore::getNumHardwareThreads()
		{
			return _scheduler->getNumHardwareThreads();
		}

		void DeviceCore::run()
		{
			assert(_initialized);
			_clock->run();
		}

		void DeviceCore::stop()
		{
			_clock->stop();
		}
	}
}