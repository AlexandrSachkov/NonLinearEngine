#ifndef NL_TIMER_H_
#define NL_TIMER_H_

#include <chrono>
#include <assert.h>

namespace NLE
{
	class Timer
	{
	public:
		Timer()
		{
			_previousTime = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
		}

		void sample()
		{
			auto time = std::chrono::high_resolution_clock::now();
			_deltaT = std::chrono::duration_cast<std::chrono::duration<double>>(time - _previousTime).count() * 0.000000001;
			_previousTime = time;
		}

		double getDeltaT()
		{
			return _deltaT;
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> _previousTime;
		double _deltaT;
	};
}

#endif
