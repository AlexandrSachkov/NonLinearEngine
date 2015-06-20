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

			for (uint_fast32_t i = 0; i < _numSystems; ++i)
			{
				if (!getSystem(i)->initialize(i, *iEngine.get()))
					return false;
				if (_executionDesc[i].getStartup() == Startup::AUTOMATIC)
				{
					scheduler->requestExecution(i);
				}			
			}
			_initialized = true;
			return true;
		}

		void SysManager::release()
		{
			for (uint_fast32_t i = 0; i < _numSystems; ++i)
			{
				_systems.at(i).get()->release();
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

		void SysManager::attachSystem(ExecutionDesc execDesc, std::unique_ptr<System> system)
		{
			assert(!_initialized);

			_systems.insert(std::make_pair<>(_numSystems, std::move(system)));
			_executionDesc.insert(std::make_pair<>(_numSystems, execDesc));
			printf("System attached: %i\n", _numSystems);
			++_numSystems;
		}
	}
}