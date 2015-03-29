#include "NL_SysManager.h"
#include "NL_System.h"
#include "tbb\tbb.h"
#include "NL_SysTask.h"
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

		bool SysManager::initialize(std::unique_ptr<Scheduler> const& scheduler)
		{
			for (uint_fast8_t i = 0; i < _numSystems; i++)
			{
				_systems.at(i).get()->initialize(i);
				scheduler->scheduleExecution(i);
			}
			return true;
		}

		void SysManager::release()
		{
			for (uint_fast8_t i = 0; i < _numSystems; i++)
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

		void SysManager::attachSystem(System* system)
		{
			_systems.insert(std::make_pair<>(_numSystems, std::unique_ptr<System>(system)));
			printf("System attached: %i\n", _numSystems);

			_numSystems++;
		}
	}
}