#ifndef NL_DEVICE_CORE_H_
#define NL_DEVICE_CORE_H_

#include <memory>

namespace NLE 
{
	namespace Core 
	{
		class Clock;
		class System;
		class SysManager;
		class Scheduler;

		class DeviceCore 
		{
		public:
			static DeviceCore& instance()
			{
				if (!_deviceCore)
				{
					_deviceCore = new DeviceCore();
				}
				return *_deviceCore;
			};

			~DeviceCore();

			bool initialize();
			void release();

			void attachSystem(System* system);

			void drive();

		private:
			DeviceCore();
			DeviceCore(DeviceCore const&) = delete;
			void operator=(DeviceCore const&) = delete;

			static DeviceCore* _deviceCore;

			std::unique_ptr<Clock> _clock;
			std::unique_ptr<SysManager> _sysManager;
			std::unique_ptr<Scheduler> _scheduler;
		};
	}
}

#endif