#include "NL_Timer.h"

namespace NLE
{
	Timer::Timer(uint_fast32_t frameAverage) :
		_frameAverage(frameAverage)
	{

	}
	Timer::~Timer()
	{

	}

	void Timer::sample()
	{
		++_currentFrameCount;
		if (_currentFrameCount >= _frameAverage)
		{
			auto time = std::chrono::high_resolution_clock::now();
			_currentFrameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(time - _previousTime).count();
			_currentFps = 1 / (_currentFrameTime / _currentFrameCount * 0.000000001);
			_previousTime = time;
			_currentFrameCount = 0;
			_fpsChanged = true;
		}
	}

	unsigned long long Timer::getFrameTimeNs()
	{
		return _currentFrameTime;
	}

	double Timer::getFps()
	{
		return _currentFps;
	}

	bool Timer::fpsChanged()
	{
		return _fpsChanged;
	}

	void Timer::reset()
	{
		_fpsChanged = false;
	}
}