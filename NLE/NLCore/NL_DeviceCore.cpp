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

		DeviceCore::DeviceCore()
		{ 
			_clock = std::make_unique<Clock>();
			_sysManager = std::make_unique<SysManager>();
			_scheduler = std::make_unique<Scheduler>();
			_uScene = std::make_unique<UScene>();
		}

		DeviceCore::~DeviceCore()
		{
			release();
		}

		bool DeviceCore::initialize()
		{
			if (!_clock->initialize())
				return false;
			if (!_scheduler->initialize())
				return false;
			if (!_sysManager->initialize())
				return false;
			if (!_uScene->initialize())
				return false;
			return true;
		}

		void DeviceCore::release()
		{
			if (_uScene)
				_uScene->release();			
			if (_sysManager)
				_sysManager->release();
			if (_scheduler)
				_scheduler->release();
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
				scheduler->executeSystems(sysMngr);
			});
		}
	}
}