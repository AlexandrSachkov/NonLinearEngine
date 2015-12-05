#include "NL_DeviceCore.h"

#include "NL_Clock.h"
#include "NL_System.h"
#include "NL_SysManager.h"
#include "NL_Scheduler.h"
#include "NL_StateManager.h"
#include "NL_ExecutionDesc.h"
#include "NL_ISystem.h"
#include "NL_Distributor.h"
#include "NL_StateManager.h"

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
		}

		DeviceCore::~DeviceCore()
		{
		}

		bool DeviceCore::initialize()
		{
			assert(!_initialized);

			if (!_clock->initialize([&](){
				_scheduler->manageExecution(_sysManager, _stateManager);
			}))
				return false;
				
			if (!_scheduler->initialize())
				return false;
			if (!_sysManager->initialize(_scheduler, *this))
				return false;
			if (!_stateManager->initialize())
				return false;
			
			_initialized = true;
			return true;
		}

		void DeviceCore::release()
		{		
			if (!_initialized)
				return;

			stopAndJoin();
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

		void DeviceCore::run()
		{
			assert(_initialized);
			_clock->run();
		}

		void DeviceCore::stop()
		{
			_clock->stop();
		}

		void DeviceCore::stopAndJoin()
		{
			_clock->stop();
			auto numRunningTasks = _scheduler->getNumRunningTasks();
			while (numRunningTasks != 0)
			{
			}
		}

		// Interface Methods

		void DeviceCore::startSystem(uint_fast32_t sysId)
		{
			_scheduler->requestExecution(sysId);
		}

		uint_fast32_t DeviceCore::getNumThreads()
		{
			return _scheduler->getNumThreads();
		}

		uint_fast32_t DeviceCore::getNumSystems()
		{
			return _sysManager->getNumSystems();
		}

		ISystem& DeviceCore::getSystemInterface(uint_fast32_t sysId)
		{
			return _sysManager->getSystem(sysId)->getInterface();
		}

		Data::Distributor& DeviceCore::getSDistributor(uint_fast32_t id)
		{
			return _stateManager->getSDistributor(id);
		}

		Data::Distributor& DeviceCore::getMSDistributor(uint_fast32_t id)
		{
			return _stateManager->getMSDistributor(id);
		}
	}
}