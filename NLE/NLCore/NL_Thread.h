#ifndef NL_THREAD_H_
#define NL_THREAD_H_

#include "tbb\atomic.h"
#include <thread>
#include <functional>

namespace NLE
{
	namespace Core
	{
		class Thread
		{
		public:
			Thread();
			~Thread();

			void setProcedure(std::function<void()> operation);
			void start();
			void stop();
			void stopAndJoin();
			bool isRunning();

		private:
			std::thread _thread;
			std::function<void()> _procedure;
			tbb::atomic<bool> _running;
			tbb::atomic<bool> _releasing;
			tbb::atomic<bool> _stopped;
		};
	}
}

#endif