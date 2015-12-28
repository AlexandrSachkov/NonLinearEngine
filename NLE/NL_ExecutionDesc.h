#ifndef NL_EXECUTION_DESC_H_
#define NL_EXECUTION_DESC_H_

#include <cstdint>
#include <chrono>
#include "tbb\atomic.h"
#include "tbb\task.h"

namespace NLE
{
	namespace Core
	{
		enum Priority	{ LOW, STANDARD, HIGH };
		enum Execution	{ NONE, SINGULAR, RECURRING };
		enum Mode		{ SYNC, ASYNC };
		enum Startup	{ MANUAL, AUTOMATIC };
		enum State		{ CREATED, INITIALIZED, RUNNING, STOPPED, RELEASED };

		class ExecutionDesc
		{
			friend class Scheduler;
			friend class DeviceCore;
		public:
			ExecutionDesc() :
				_priority(Priority::STANDARD),
				_execution(Execution::RECURRING),
				_mode(Mode::ASYNC),
				_startup(Startup::AUTOMATIC),
				_periodNs(0L)
			{
				_enabled.fetch_and_store(true);
				_state = State::CREATED;
			}

			ExecutionDesc(
				Priority priority,
				Execution execution,
				Mode mode,
				Startup startup,
				unsigned long long periodNs
				) :
				_priority(priority),
				_execution(execution),
				_mode(mode),
				_startup(startup),
				_periodNs(std::chrono::nanoseconds(periodNs))
			{
				_enabled.fetch_and_store(true);
				_state = State::CREATED;
			}

			Priority getPriority()
			{
				return _priority;
			}

			Execution getExecution()
			{
				return _execution;
			}

			Mode getMode()
			{
				return _mode;
			}

			Startup getStartup()
			{
				return _startup;
			}
			
			bool enabled()
			{
				return _enabled.load();
			}

			State getState()
			{
				return _state;
			}

		private:
			bool isTimeToStart()
			{
				return std::chrono::high_resolution_clock::now() >= _startTime;
			}
			
			void resetStartTime()
			{
				_startTime = std::chrono::high_resolution_clock::now() + _periodNs;
			}	
			
			void enable(bool enable)
			{
				_enabled.fetch_and_store(enable);
			}	

			void setState(State state)
			{
				_state = state;
			}

			Priority _priority;
			Execution _execution;
			Mode _mode;
			Startup _startup;
			State _state;
			std::chrono::duration<unsigned long long, std::nano> _periodNs;
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> _startTime;
			tbb::atomic<bool> _enabled;
		};
	}
}

#endif