#include "NL_SysManager.h"

#include "NL_StateManager.h"
#include "NL_System.h"
#include "NL_SysTask.h"
#include "NL_SysRuntimeControl.h"
#include "tbb\tbb.h"

namespace NLE 
{
	namespace Core 
	{
		SysManager::SysManager() :
			_numSystems(0)
		{

		}

		SysManager::~SysManager()
		{

		}

		bool SysManager::initialize(
			std::unique_ptr<Scheduler> const& scheduler,
			std::unique_ptr<StateManager> const& stateManager,
			std::unique_ptr<SysRuntimeControl> const& sysRuntimeControl)
		{
			for (uint_fast8_t i = 0; i < _numSystems; ++i)
			{
				if (!getSystem(i)->initialize(i, stateManager.get(), *sysRuntimeControl.get()))
					return false;
				if (_executionDesc[i].getStartup() == Startup::AUTOMATIC)
				{
					scheduler->requestExecution(i);
				}			
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

		ExecutionDesc& SysManager::getExecutionDesc(uint_fast8_t sysId)
		{
			return _executionDesc.at(sysId);
		}

		std::unique_ptr<System> const& SysManager::getSystem(uint_fast8_t sysId) const
		{
			return _systems.at(sysId);
		}

		void SysManager::attachSystem(ExecutionDesc execDesc, std::unique_ptr<System> system)
		{
			_systems.insert(std::make_pair<>(_numSystems, std::move(system)));
			_executionDesc.insert(std::make_pair<>(_numSystems, execDesc));
			printf("System attached: %i\n", _numSystems);
			++_numSystems;
		}
	}
}