#ifndef NL_SYS_MANAGER_H_
#define NL_SYS_MANAGER_H_

#include <memory>
#include <unordered_map>
#include "NL_ExecutionDesc.h"

namespace NLE 
{
	namespace Core 
	{
		class System;
		class Scheduler;
		class UObject;
		class StateManager;
		class IEngine;

		class SysManager 
		{
		public:
			SysManager();
			~SysManager();

			bool initialize(
				std::unique_ptr<Scheduler> const& scheduler,
				std::unique_ptr<IEngine> const& iEngine);
			void release();

			uint_fast32_t getNumSystems();
			ExecutionDesc& getExecutionDesc(uint_fast32_t sysId);

			std::unique_ptr<System> const& getSystem(uint_fast32_t sysId) const;
			void attachSystem(ExecutionDesc execDesc, std::unique_ptr<System> system);
		private:
			std::unordered_map<uint_fast32_t, std::unique_ptr<System>> _systems;
			std::unordered_map<uint_fast32_t, ExecutionDesc> _executionDesc;
			uint_fast32_t _numSystems;

			bool _initialized;
		};
	}
}

#endif