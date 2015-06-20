#include "NL_SysManager.h"

#include "NL_StateManager.h"
#include "NL_System.h"
#include "NL_SysTask.h"
#include "NL_IEngine.h"
#include "tbb\tbb.h"
#include <assert.h>

namespace NLE 
{
	namespace Core 
	{
		SysManager::SysManager() :
			_numSystems(0),
			_initialized(false)
		{

		}

		SysManager::~SysManager()
		{

		}

		bool SysManager::initialize(
			std::unique_ptr<Scheduler> const& scheduler,
			std::unique_ptr<IEngine> const& iEngine)
		{
			assert(!_initialized);

			for (auto& system : _systems)
			{
				if (!system.second->initialize(*iEngine.get()))
					return false;
				if (_executionDesc[system.first].getStartup() == Startup::AUTOMATIC)
				{
					scheduler->requestExecution(system.first);
				}
			}
			_initialized = true;
			return true;
		}

		void SysManager::release()
		{
			for (auto& system : _systems)
			{
				system.second->release();
			}
			_systems.clear();
			_numSystems = 0;

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

		std::unique_ptr<System> const& SysManager::getSystem(uint_fast32_t sysId) const
		{
			return _systems.at(sysId);
		}

		void SysManager::attachSystem(uint_fast32_t sysId, ExecutionDesc execDesc, std::unique_ptr<System> system)
		{
			assert(!_initialized);

			_systems.insert(std::make_pair<>(sysId, std::move(system)));
			_executionDesc.insert(std::make_pair<>(sysId, execDesc));
			printf("System attached: %i\n", sysId);
			++_numSystems;
		}
	}
}