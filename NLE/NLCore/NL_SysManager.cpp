#include "NL_SysManager.h"
#include "NL_System.h"
#include "NL_UScene.h"
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

		void SysManager::attachSystem(
			std::unique_ptr<Scheduler> const& scheduler,
			std::unique_ptr<UScene> const& uScene,
			System* system)
		{
			_systems.insert(std::make_pair<>(system->getID(), std::unique_ptr<System>(system)));
			if (system->getScene())
			{
				uScene->attachScene(system->getID(), system->getScene());
			}
			
			scheduler->scheduleExecution(system->getID());
			
			printf("System attached: %i\n", system->getID());
		}
	}
}