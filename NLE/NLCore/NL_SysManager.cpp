#include "NL_SysManager.h"

#include "NL_StateManager.h"
#include "NL_System.h"
#include "NL_IEngine.h"
#include "NL_Scheduler.h"
#include "NL_SysInitializer.h"

#include "tbb\tbb.h"
#include <assert.h>

namespace NLE 
{
	namespace Core 
	{
		SysManager::SysManager() :
			_numSystems(0),
			_numSysThreads(0),
			_initialized(false)
		{

		}

		SysManager::~SysManager()
		{

		}

		bool SysManager::initialize(
			std::unique_ptr<Scheduler> const& scheduler,
			IEngine& iEngine)
		{
			assert(!_initialized);

			for (uint_fast32_t& sysId : _sysInitOrder)
			{
				assert(_systems.count(sysId) > 0 && _executionDesc.count(sysId) > 0);
				if (!_systems.at(sysId)->initialize(iEngine, _initializers.at(sysId)))
					return false;

				auto execDesc = _executionDesc.at(sysId);
				if (execDesc.getExecution() != Execution::NONE && execDesc.getStartup() == Startup::AUTOMATIC)
				{
					scheduler->startSystem(getExecutionDesc(sysId),sysId);
				}
			}

			_initialized = true;
			return true;
		}

		void SysManager::release()
		{
			if (!_initialized)
				return;

			for (auto& system : _systems)
			{
				system.second->release();
			}
			_systems.clear();
			_numSystems = 0;
			_initializers.clear();
			_sysThreads.clear();
			_numSysThreads = 0;

			_initialized = false;
		}

		uint_fast32_t SysManager::getNumSystems()
		{
			return _numSystems;
		}

		ExecutionDesc& SysManager::getExecutionDesc(uint_fast32_t sysId)
		{
			return _executionDesc.at(sysId);
		}

		std::unique_ptr<System> const& SysManager::getSystem(uint_fast32_t sysId)
		{
			return _systems.at(sysId);
		}

		uint_fast32_t SysManager::getNumSysThreads()
		{
			return _numSysThreads;
		}

		std::unique_ptr<SysThread> const& SysManager::getSystemThread(uint_fast32_t sysId)
		{
			return _sysThreads.at(sysId);
		}

		void SysManager::attachSystem(uint_fast32_t sysId, ExecutionDesc& execDesc, std::unique_ptr<System> system)
		{
			assert(!_initialized);

			_systems.insert(std::make_pair<>(sysId, std::move(system)));
			_executionDesc.insert(std::make_pair<>(sysId, execDesc));
			_initializers.insert(std::make_pair<>(sysId, nullptr));
			_sysInitOrder.push_back(sysId);
			
			if (execDesc.getMethod() == Method::THREAD)
			{
				_sysThreads.insert(std::make_pair<>(sysId, std::make_unique<SysThread>(sysId, 100000L)));
				++_numSysThreads;
			}

			++_numSystems;
		}

		void SysManager::setSystemInitializer(uint_fast32_t sysId, std::unique_ptr<SysInitializer> initializer)
		{
			assert(!_initialized);
			_initializers.at(sysId) = std::move(initializer);
		}
	}
}