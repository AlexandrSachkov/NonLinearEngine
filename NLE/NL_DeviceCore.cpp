#include "NL_DeviceCore.h"

#include "NL_System.h"
#include "NL_Scheduler.h"
#include "NL_ExecutionDesc.h"
#include "NL_ISystem.h"
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
			_numSystems(0)
		{ 
			_running.store(false);
			_scheduler = std::make_unique<Scheduler>();
		}

		DeviceCore::~DeviceCore()
		{
		}

		bool DeviceCore::initialize()
		{
			assert(!_initialized);
				
			if (!_scheduler->initialize((uint_fast32_t)_threads.size()))
				return false;

			for (uint_fast32_t& sysId : _sysInitOrder)
			{
				assert(_systems.count(sysId) > 0 && _executionDesc.count(sysId) > 0);
				if (!_systems.at(sysId)->initialize(_initializers.at(sysId)))
					return false;

				auto& execDesc = _executionDesc.at(sysId);
				execDesc.setState(State::INITIALIZED);
				if (execDesc.getExecution() != Execution::NONE && execDesc.getStartup() == Startup::AUTOMATIC)
				{
					_toStart.push(sysId);
				}
			}
			
			_initialized = true;
			return true;
		}

		void DeviceCore::release()
		{		
			if (!_initialized)
				return;

			stopAndJoin();

			for (auto& system : _systems)
			{
				system.second->release();
				_executionDesc.at(system.first).setState(State::RELEASED);
			}
			_systems.clear();
			_numSystems = 0;
			_initializers.clear();
			_threads.clear();

			if (_scheduler)
				_scheduler->release();

			_initialized = false;
		}

		Thread& DeviceCore::allocateThread()
		{
			_threads.push_back(std::make_unique<Thread>(100000L));
			return *_threads.at(_threads.size() - 1).get();
		}

		void DeviceCore::attachSystem(uint_fast32_t sysId, ExecutionDesc& executionDesc, std::unique_ptr<System> system)
		{
			assert(!_initialized);

			_systems.insert(std::make_pair<>(sysId, std::move(system)));
			_executionDesc.insert(std::make_pair<>(sysId, executionDesc));
			_initializers.insert(std::make_pair<>(sysId, nullptr));
			_sysInitOrder.push_back(sysId);

			++_numSystems;
		}

		void DeviceCore::setNumThreads(uint_fast32_t numThreads)
		{
			_scheduler->setNumThreads(numThreads);
		}

		void DeviceCore::run()
		{
			assert(_initialized);
			_running.store(true);
			while (_running == true)
			{
				uint_fast32_t sysId;
				ExecutionDesc* desc;
				if (!_toStart.empty())
				{
					while (_toStart.try_pop(sysId))
					{
						desc = &_executionDesc.at(sysId);
						if (desc->getExecution() != Execution::NONE)
						{
							desc->enable(true);
							_systems.at(sysId)->start();
							desc->setState(State::RUNNING);
							_scheduler->scheduleExecution(sysId);
						}
					}
				}
				if (!_toStop.empty())
				{
					while (_toStop.try_pop(sysId))
					{
						desc = &_executionDesc.at(sysId);						
						desc->enable(false);
						desc->setState(State::STOPPED);						
					}
				}
				
				_scheduler->manageExecution(_systems, _executionDesc);
			}
			for (auto& system : _systems)
			{
				if (_executionDesc.at(system.first).getState() == State::RUNNING)
				{
					system.second->stop();
				}
			}
		}

		void DeviceCore::stop()
		{
			_running.store(false);
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
			_toStart.push(sysId);
		}

		void DeviceCore::stopSystem(uint_fast32_t sysId)
		{
			_toStop.push(sysId);
		}

		uint_fast32_t DeviceCore::getNumThreads()
		{
			return _scheduler->getNumThreads();
		}

		uint_fast32_t DeviceCore::getNumSystems()
		{
			return _numSystems;
		}

		ISystem& DeviceCore::getSystemInterface(uint_fast32_t sysId)
		{
			return _systems.at(sysId)->getInterface();
		}

		void DeviceCore::setSystemInitializer(uint_fast32_t sysId, std::unique_ptr<SysInitializer> initializer)
		{
			assert(!_initialized);
			_initializers.at(sysId) = std::move(initializer);
		}

		void DeviceCore::runAsync(std::function<void()>& operation, Priority priority)
		{
			_scheduler->runAsync(operation, priority);
		}
	}
}