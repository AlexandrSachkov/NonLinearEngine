#include "NL_DeviceCore.h"

#include "NL_Clock.h"
#include "NL_System.h"
#include "NL_SysManager.h"
#include "NL_Scheduler.h"
#include "NL_UScene.h"

namespace NLE 
{
	namespace Core 
	{
		DeviceCore *DeviceCore::_deviceCore = nullptr;

		DeviceCore::DeviceCore() : 
			_clock(new Clock()),
			_sysManager(new SysManager()),
			_scheduler(new Scheduler()),
			_uScene(new UScene())
		{ 
			
		}

		DeviceCore::~DeviceCore()
		{

		}

		bool DeviceCore::initialize()
		{
			if (!_clock->initialize())
				return false;
			if (!_sysManager->initialize())
				return false;
			if (!_scheduler->initialize())
				return false;
			if (!_uScene->initialize())
				return false;
			return true;
		}

		void DeviceCore::release()
		{
			if (_uScene)
				_uScene->release();
			if (_scheduler)
				_scheduler->release();
			if (_sysManager)
				_sysManager->release();
			if (_clock)
				_clock->release();
		}

		void DeviceCore::attachSystem(System* system)
		{
			_sysManager->attachSystem(_scheduler, _uScene, system);
		}

		void DeviceCore::addObject(UObject* object)
		{
			_uScene->addObject(object);
		}

		void DeviceCore::drive()
		{
			std::unique_ptr<Scheduler>& scheduler = _scheduler;
			std::unique_ptr<SysManager>& sysMngr = _sysManager;
			_clock->onTick([&scheduler, &sysMngr](){
				//printf("running\n");
				scheduler->executeSystems(sysMngr);
			});
			//printf("FINISHED ENQUEUING");
		}
	}
}