#include "NL_SysManager.h"

#include "NL_StateManager.h"
#include "NL_System.h"
#include "NL_SysTask.h"
#include "tbb\tbb.h"

namespace NLE 
{
	namespace Core 
	{
		SysManager::SysManager() :
			_systems(),
			_numSystems(0)
		{

		}

		SysManager::~SysManager()
		{

		}

		bool SysManager::initialize(
			std::unique_ptr<Scheduler> const& scheduler,
			std::unique_ptr<StateManager> const& stateManager)
		{
			for (uint_fast8_t i = 0; i < _numSystems; ++i)
			{
				System* system = _systems.at(i).get();
				if (!system->initialize(i, stateManager))
					return false;
				scheduler->scheduleExecution(system->getExecutionDesc());
			}
			return true;
		}

		void SysManager::release()
		{
			for (uint_fast8_t i = 0; i < _numSystems; ++i)
			{
				_systems.at(i).get()->release();
			}
		}

		uint_fast8_t SysManager::getNumSystems()
		{
			return _numSystems;
		}

		std::unique_ptr<System> const& SysManager::getSystemById(uint_fast8_t sysId) const
		{
			return _systems.at(sysId);
		}

		void SysManager::attachSystem(std::unique_ptr<System> system)
		{
			_systems.insert(std::make_pair<>(_numSystems, std::move(system)));			
			printf("System attached: %i\n", _numSystems);
			++_numSystems;
		}
	}
}