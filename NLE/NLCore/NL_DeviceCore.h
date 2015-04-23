#ifndef NL_DEVICE_CORE_H_
#define NL_DEVICE_CORE_H_

#include <memory>

namespace NLE 
{
	namespace Core 
	{
		class Clock;
		class Scheduler;
		class System;
		class SysManager;
		class StateManager;
		
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

			void attachSystem(std::unique_ptr<System> system);
			void attachStateManager(std::unique_ptr<StateManager> stateManager);
			void setClockPeriodNs(unsigned long long periodNs);
			void run();
			void stop();

		private:
			DeviceCore();
			DeviceCore(DeviceCore const&) = delete;
			void operator=(DeviceCore const&) = delete;

			static DeviceCore* _deviceCore;

			std::unique_ptr<Clock> _clock;
			std::unique_ptr<SysManager> _sysManager;
			std::unique_ptr<Scheduler> _scheduler;
			std::unique_ptr<StateManager> _stateManager;
		};
	}
}

#endif