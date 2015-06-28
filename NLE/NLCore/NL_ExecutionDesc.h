#ifndef NL_EXECUTION_DESC_H_
#define NL_EXECUTION_DESC_H_

#include <cstdint>
#include <chrono>

namespace NLE
{
	namespace Core
	{
		enum Priority	{ LOW, STANDARD, HIGH };
		enum Execution	{ NONE, SINGULAR, RECURRING };
		enum Mode		{ SYNC, ASYNC };
		enum Startup	{ MANUAL, AUTOMATIC };

		class ExecutionDesc
		{
			friend class Scheduler;
		public:
			ExecutionDesc() :
				_priority(Priority::STANDARD),
				_execution(Execution::RECURRING),
				_mode(Mode::ASYNC),
				_startup(Startup::AUTOMATIC),
				_periodNs(0L)
			{
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

		private:
			bool isTimeToStart()
			{
				return std::chrono::high_resolution_clock::now() >= _startTime;
			}
			
			void resetStartTime()
			{
				_startTime = std::chrono::high_resolution_clock::now() + _periodNs;
			}

			Priority _priority;
			Execution _execution;
			Mode _mode;
			Startup _startup;
			std::chrono::duration<unsigned long long, std::nano> _periodNs;
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> _startTime;
		};
	}
}

#endif