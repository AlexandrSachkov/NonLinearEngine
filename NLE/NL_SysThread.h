#ifndef NL_SYS_THREAD_H_
#define NL_SYS_THREAD_H_

#include "NL_Scheduler.h"
#include "tbb\atomic.h"
#include <thread>
#include <functional>
#include <chrono>
#include <cstdint>

namespace NLE
{
	namespace Core
	{		
		class SysThread
		{
			friend class Scheduler;
		public:
			SysThread(uint_fast32_t sysId, unsigned long long sleepPeriodNs);
			~SysThread();		

		private:
			void setProcedure(Scheduler* scheduler, std::function<void()> operation);
			void start();
			void stop();
			void stopAndJoin();
			bool isRunning();
			void resume();

			std::chrono::duration<unsigned long long, std::nano> _sleepPeriodNs;
			std::thread _thread;
			std::function<void()> _procedure;
			tbb::atomic<bool> _running;
			tbb::atomic<bool> _releasing;
			tbb::atomic<bool> _stopped;
			tbb::atomic<bool> _paused;
			uint_fast32_t _sysId;
			Scheduler* _scheduler;
		};
	}
}

#endif