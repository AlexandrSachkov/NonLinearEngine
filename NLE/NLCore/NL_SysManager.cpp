#include "NL_SysManager.h"
#include "NL_System.h"

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

		void SysManager::attachSystem(System* system)
		{
			_systems.insert(std::make_pair<>(system->getID(), std::unique_ptr<System>(system)));
			printf("System attached: %i\n", system->getID());
		}

		void SysManager::executeSystems(){
			std::unordered_map<int, std::unique_ptr<System>>::iterator it;
			for (it = _systems.begin(); it != _systems.end(); it++)
			{
				tbb::task::enqueue(*it->second.get());
				
				//it->second->execute();
			}
		}
	}
}