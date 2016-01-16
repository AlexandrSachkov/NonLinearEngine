#include "NL_Thread.h"

#include <assert.h>

namespace NLE
{
	namespace Core
	{
		Thread::Thread(unsigned long long sleepPeriodNs) :
			_sleepPeriodNs(std::chrono::nanoseconds(sleepPeriodNs))
		{
			_running.store(false);
			_releasing.store(false);
			_stopped.store(true);
			_runProcedure = []() {};
			_releaseProcedure = []() {};

			_thread = std::thread([&](
				std::chrono::duration<unsigned long long, std::nano>& sleepPeriod,
				tbb::atomic<bool>& running,
				tbb::atomic<bool>& releasing,
				tbb::atomic<bool>& stopped,
				std::function<void()>& runOperation,
				std::function<void()>& releaseOperation
				) {
				while (!releasing)
				{
					while (!running && !releasing)
					{
						std::this_thread::sleep_for(sleepPeriod);
					}
					stopped.store(false);
					while (running)
					{
						runOperation();
					}
					stopped.store(true);
				}
				releaseOperation();
			}, std::ref(_sleepPeriodNs), std::ref(_running), std::ref(_releasing), std::ref(_stopped), std::ref(_runProcedure), std::ref(_releaseProcedure));
		}

		Thread::~Thread()
		{
			_running.store(false);
			_releasing.store(true);				
			if (_thread.joinable())
				_thread.join();
		}

		void Thread::setProcedure(std::function<void()> runOperation, std::function<void()> releaseOperation)
		{
			if (_running)
			{
				stopAndJoin();
				_runProcedure = runOperation;
				_releaseProcedure = releaseOperation;
				start();
			}
			else
			{
				_runProcedure = runOperation;
				_releaseProcedure = releaseOperation;
			}			
		}

		void Thread::start()
		{
			_running.store(true);
		}

		void Thread::stop()
		{
			_running.store(false);
		}

		void Thread::stopAndJoin()
		{
			_running.store(false);
			while (!_stopped)
			{
			}
		}

		bool Thread::isRunning()
		{
			return _running.load();
		}
	}
}