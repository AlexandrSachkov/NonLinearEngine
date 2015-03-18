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

		void SysManager::attachSystem(System* system)
		{
			_systems.insert(std::make_pair<>(system->getID(), std::unique_ptr<System>(system)));
			printf("System attached: %i\n", system->getID());
		}

		void SysManager::executeSystems(){
			std::unordered_map<int, std::unique_ptr<System>>::iterator it;
			for (it = _systems.begin(); it != _systems.end(); it++)
			{
				NLE::Core::SysTask& myTask = *it->second.get()->getTask();
				tbb::task::enqueue(myTask);
				//it->second->execute();
			}
		}
	}
}