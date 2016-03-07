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

		double deltaT()
		{
			auto time = std::chrono::high_resolution_clock::now();
			double deltaT = std::chrono::duration_cast<std::chrono::duration<double>>(time - _previousTime).count() * 0.000000001;
			_previousTime = time;
			return deltaT;
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> _previousTime;
	};
}

#endif
