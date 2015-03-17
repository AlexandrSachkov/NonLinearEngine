#ifndef NL_SYS_MANAGER_H_
#define NL_SYS_MANAGER_H_

#include <memory>
#include <unordered_map>

namespace NLE 
{
	namespace Core 
	{
		class System;

		class SysManager 
		{
		public:
			SysManager();
			~SysManager();

			bool initialize();
			void release();

			void attachSystem(System* system);
			void executeSystems();

		private:
			std::unordered_map<int, std::unique_ptr<System>> _systems;
		};
	}
}

#endif