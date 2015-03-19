#ifndef NL_SCHEDULER_H_
#define NL_SCHEDULER_H_

#include "tbb/concurrent_queue.h"

namespace NLE 
{
	namespace Core 
	{
		class SysManager;
		class Scheduler 
		{
		public:
			Scheduler();
			~Scheduler();

			bool initialize();
			void release();

			void scheduleExecution(uint_fast8_t sysId);
			void executeSystems(std::unique_ptr<SysManager> const& sysManager);

		private:
			tbb::concurrent_queue<uint_fast8_t> _scheduledSystems;
		};
	}
}

#endif