#include "NL_DeviceCore.h"

#include "NL_System.h"
#include "NL_SysManager.h"
#include "NL_Scheduler.h"
#include "NL_StateManager.h"
#include "NL_ExecutionDesc.h"
#include "NL_ISystem.h"
#include "NL_Distributor.h"
#include "NL_StateManager.h"
#include "NL_SysInitializer.h"

#include <cassert>
#include "tbb\spin_mutex.h"

namespace NLE 
{
	namespace Core 
	{
		DeviceCore* DeviceCore::_deviceCore = nullptr;

		DeviceCore::DeviceCore() :
			_initialized(false),
			_running(false)
		{ 
			_runningLock = new tbb::spin_mutex();

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
				
			if (!_scheduler->initialize(_sysManager->getNumSysThreads()))
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

			_initialized = false;
		}

		void DeviceCore::attachSystem(uint_fast32_t sysId, ExecutionDesc& executionDesc, std::unique_ptr<System> system)
		{
			_sysManager->attachSystem(sysId, executionDesc, std::move(system));
		}

		void DeviceCore::setNumThreads(uint_fast32_t numThreads)
		{
			_scheduler->setNumThreads(numThreads);
		}

		void DeviceCore::run()
		{
			assert(_initialized);
			_runningLock->lock();
			_running = true;
			_runningLock->unlock();

			while (_running == true)
			{
				_scheduler->manageExecution(_sysManager, _stateManager);
			}
		}

		void DeviceCore::stop()
		{
			_runningLock->lock();
			_running = false;
			_runningLock->unlock();
		}

		void DeviceCore::stopAndJoin()
		{
			stop();
			while (_scheduler->getNumRunningTasks() > 0)
			{
			}
		}


		//Interface Methods
		void DeviceCore::startSystem(uint_fast32_t sysId)
		{
			_scheduler->startSystem(_sysManager->getExecutionDesc(sysId), sysId);
		}

		void DeviceCore::stopSystem(uint_fast32_t sysId)
		{
			_scheduler->stopSystem(_sysManager->getExecutionDesc(sysId), sysId);
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

		void DeviceCore::setSystemInitializer(uint_fast32_t sysId, std::unique_ptr<SysInitializer> initializer)
		{
			_sysManager->setSystemInitializer(sysId, std::move(initializer));
		}
	}
}