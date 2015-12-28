#ifndef NL_DEVICE_CORE_H_
#define NL_DEVICE_CORE_H_

#include "NL_IEngine.h"
#include "NL_Thread.h"

#include "tbb/atomic.h"
#include "tbb/concurrent_queue.h"

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

			Thread& allocateThread();
			void attachSystem(uint_fast32_t sysId, ExecutionDesc& executionDesc, std::unique_ptr<System> system);
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
			void setSystemInitializer(uint_fast32_t sysId, std::unique_ptr<SysInitializer> initializer);

		private:
			DeviceCore();
			DeviceCore(DeviceCore const&) = delete;
			void operator=(DeviceCore const&) = delete;

			static DeviceCore* _deviceCore;
			tbb::atomic<bool> _running;

			std::unique_ptr<Scheduler> _scheduler;
			bool _initialized;

			std::unordered_map<uint_fast32_t, std::unique_ptr<System>> _systems;
			std::vector<uint_fast32_t> _sysInitOrder;
			std::unordered_map<uint_fast32_t, ExecutionDesc> _executionDesc;
			std::unordered_map<uint_fast32_t, std::unique_ptr<SysInitializer>> _initializers;
			uint_fast32_t _numSystems;
			std::vector<std::unique_ptr<Thread>> _threads;

			tbb::concurrent_queue<uint_fast32_t> _toStart;
			tbb::concurrent_queue<uint_fast32_t> _toStop;
		};
	}
}

#include "NL_DeviceCore.inl"

#endif