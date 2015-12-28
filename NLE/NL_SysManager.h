#ifndef NL_SYS_MANAGER_H_
#define NL_SYS_MANAGER_H_

#include "NL_ExecutionDesc.h"
#include "NL_SysThread.h"

#include <memory>
#include <unordered_map>


namespace NLE 
{
	namespace Core 
	{
		class System;
		class Scheduler;
		class UObject;
		class StateManager;
		class IEngine;
		struct SysInitializer;

		class SysManager 
		{
		public:
			SysManager();
			~SysManager();

			bool initialize(
				std::unique_ptr<Scheduler> const& scheduler,
				IEngine& iEngine);
			void release();

			uint_fast32_t getNumSystems();
			ExecutionDesc& getExecutionDesc(uint_fast32_t sysId);			

			std::unique_ptr<System> const& getSystem(uint_fast32_t sysId);
			std::unique_ptr<SysThread> const& getSystemThread(uint_fast32_t sysId);
			uint_fast32_t getNumSysThreads();
			void attachSystem(uint_fast32_t sysId, ExecutionDesc& execDesc, std::unique_ptr<System> system);
			void setSystemInitializer(uint_fast32_t sysId, std::unique_ptr<SysInitializer> initializer);

		private:
			std::unordered_map<uint_fast32_t, std::unique_ptr<System>> _systems;
			std::vector<uint_fast32_t> _sysInitOrder;
			std::unordered_map<uint_fast32_t, ExecutionDesc> _executionDesc;
			std::unordered_map<uint_fast32_t, std::unique_ptr<SysThread>> _sysThreads;
			uint_fast32_t _numSysThreads;
			std::unordered_map<uint_fast32_t, std::unique_ptr<SysInitializer>> _initializers;
			uint_fast32_t _numSystems;

			bool _initialized;
		};
	}
}

#endif