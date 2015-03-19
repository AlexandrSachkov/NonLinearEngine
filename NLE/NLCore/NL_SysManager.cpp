#include "NL_SysManager.h"
#include "NL_System.h"
#include "tbb\tbb.h"
#include "NL_SysTask.h"
namespace NLE 
{
	namespace Core 
	{
		SysManager::SysManager() :
			_systems() 
		{

		}

		SysManager::~SysManager()
		{

		}

		bool SysManager::initialize()
		{
			return true;
		}

		void SysManager::release()
		{

		}

		std::unique_ptr<System> const& SysManager::getSystemById(uint_fast8_t sysId) const
		{
			return _systems.at(sysId);
		}

		void SysManager::attachSystem(System* system, std::unique_ptr<Scheduler> const& scheduler)
		{
			_systems.insert(std::make_pair<>(system->getID(), std::unique_ptr<System>(system)));
			scheduler->scheduleExecution(system->getID());
			
			printf("System attached: %i\n", system->getID());
		}
	}
}