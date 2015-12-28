#ifndef NL_DEVICE_CORE_H_
#define NL_DEVICE_CORE_H_

#include "NL_IEngine.h"

#include <memory>
#include <cstdint>
#include <functional>

namespace tbb
{
	class spin_mutex;
}
namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			class Distributor;
		}

		class Scheduler;
		class System;
		class SysManager;
		class StateManager;
		class ExecutionDesc;
		class ISystem;
		struct SysInitializer;

		class DeviceCore : public IEngine
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

			void attachSystem(uint_fast32_t sysId, ExecutionDesc& executionDesc, std::unique_ptr<System> system);

			template <typename T>
			void installMSContainer(uint_fast32_t id, uint_fast32_t initialSize, uint_fast32_t grainSize);

			template <typename T>
			void installSContainer(uint_fast32_t id, uint_fast32_t size, uint_fast32_t grainSize);

			void setNumThreads(uint_fast32_t numThreads);
			
			void run();
			void stop();
			void stopAndJoin();
			
			//Interface Methods
			void startSystem(uint_fast32_t sysId);
			void stopSystem(uint_fast32_t sysId);
			uint_fast32_t getNumThreads();	
			uint_fast32_t getNumSystems();
			ISystem& getSystemInterface(uint_fast32_t sysId);
			Data::Distributor& getSDistributor(uint_fast32_t id);
			Data::Distributor& getMSDistributor(uint_fast32_t id);
			void setSystemInitializer(uint_fast32_t sysId, std::unique_ptr<SysInitializer> initializer);

		private:
			DeviceCore();
			DeviceCore(DeviceCore const&) = delete;
			void operator=(DeviceCore const&) = delete;

			static DeviceCore* _deviceCore;
			tbb::spin_mutex* _runningLock;
			bool _running;

			std::unique_ptr<SysManager> _sysManager;
			std::unique_ptr<Scheduler> _scheduler;
			std::unique_ptr<StateManager> _stateManager;

			bool _initialized;
		};
	}
}

#include "NL_DeviceCore.inl"

#endif