#include "NL_Thread.h"

#include <assert.h>

namespace NLE
{
	namespace Core
	{
		Thread::Thread(unsigned long long sleepPeriodNs) :
			_sleepPeriodNs(std::chrono::nanoseconds(sleepPeriodNs))
		{
			_running.fetch_and_store(false);
			_releasing.fetch_and_store(false);
			_stopped.fetch_and_store(true);
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
					stopped.fetch_and_store(false);
					while (running)
					{
						runOperation();
					}
					stopped.fetch_and_store(true);
				}
				releaseOperation();
			}, std::ref(_sleepPeriodNs), std::ref(_running), std::ref(_releasing), std::ref(_stopped), std::ref(_runProcedure), std::ref(_releaseProcedure));
		}

		Thread::~Thread()
		{
			_running.fetch_and_store(false);
			_releasing.fetch_and_store(true);				
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
			_running.fetch_and_store(true);
		}

		void Thread::stop()
		{
			_running.fetch_and_store(false);
		}

		void Thread::stopAndJoin()
		{
			_running.fetch_and_store(false);
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