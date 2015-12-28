#include "NL_SysThread.h"

#include <assert.h>

namespace NLE
{
	namespace Core
	{
		SysThread::SysThread(uint_fast32_t sysId, unsigned long long sleepPeriodNs) :
			_sysId(sysId),
			_sleepPeriodNs(std::chrono::nanoseconds(sleepPeriodNs)),
			_scheduler(nullptr)
		{
			_running.store(false);
			_releasing.store(false);
			_stopped.store(true);
			_paused.store(true);
			_procedure = []() {};

			_thread = std::thread([&](
				std::chrono::duration<unsigned long long, std::nano>& sleepPeriod,
				tbb::atomic<bool>& running,
				tbb::atomic<bool>& releasing,
				tbb::atomic<bool>& stopped,
				tbb::atomic<bool>& paused,
				std::function<void()>& operation,
				Scheduler*& scheduler
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
						operation();					
						
						paused.store(true);
						scheduler->signalFinished(_sysId);
						while (paused && running)
						{
						}										
					}
					stopped.store(true);
				}
			}, 
				std::ref(_sleepPeriodNs), 
				std::ref(_running), 
				std::ref(_releasing), 
				std::ref(_stopped), 
				std::ref(_paused),
				std::ref(_procedure),
				std::ref(_scheduler));
		}

		SysThread::~SysThread()
		{
			_running.store(false);
			_releasing.store(true);
			if (_thread.joinable())
				_thread.join();
		}

		void SysThread::setProcedure(Scheduler* scheduler, std::function<void()> operation)
		{
			assert(_stopped);
			_scheduler = scheduler;
			_procedure = operation;
		}

		void SysThread::start()
		{		
			_running.store(true);
		}

		void SysThread::stop()
		{
			_running.store(false);
		}

		void SysThread::stopAndJoin()
		{
			_running.store(false);
			while (!_stopped)
			{
			}
		}

		bool SysThread::isRunning()
		{
			return _running.load();
		}

		void SysThread::resume()
		{
			_paused.store(false);
		}
	}
}