#ifndef NL_SYS_MANAGER_H_
#define NL_SYS_MANAGER_H_

#include <memory>
#include <unordered_map>

namespace NLE 
{
	namespace Core 
	{
		class System;
		class Scheduler;
		class UScene;
		class UObject;
		class SysManager 
		{
		public:
			SysManager();
			~SysManager();

			bool initialize();
			void release();

			std::unique_ptr<System> const& getSystemById(uint_fast8_t sysId) const;
			void attachSystem(
				std::unique_ptr<Scheduler> const& scheduler,
				std::unique_ptr<UScene> const& uScene,
				System* system);
		private:
			std::unordered_map<uint_fast8_t, std::unique_ptr<System>> _systems;
		};
	}
}

#endif