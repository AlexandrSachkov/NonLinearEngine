#ifndef NL_TIMER_H_
#define NL_TIMER_H_

#include <chrono>

namespace NLE
{
	class Timer
	{
	public:
		Timer(uint_fast32_t frameAverage);
		~Timer();

		void sample();

		unsigned long long getFrameTimeNs();
		double getFps();
		bool fpsChanged();
		void reset();

	private:
		uint_fast32_t _frameAverage;
		uint_fast32_t _currentFrameCount;
		std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> _previousTime;
		unsigned long long _currentFrameTime;
		double _currentFps;
		bool _fpsChanged;
	};
}

#endif
