#include "NL_Clock.h"
#include <thread>

namespace NLE
{
	namespace Core
	{
		Clock::Clock() :
			_frequencyNs(std::chrono::nanoseconds(1000000L))
		{
			_running.fetch_and_store(false);
		}

		Clock::~Clock()
		{

		}

		void Clock::setFrequencyNs(unsigned long long frequencyNs)
		{
			_frequencyNs = std::chrono::nanoseconds(frequencyNs);
		}

		bool Clock::initialize(std::function<void()> operation)
		{
			_operation = operation;
			return true;
		}

		void Clock::release()
		{

		}

		void Clock::run()
		{
			_running.fetch_and_store(true);
			while (_running ==  true)
			{
				auto start = std::chrono::high_resolution_clock::now();
				_operation();
				auto end = std::chrono::high_resolution_clock::now();
				std::this_thread::sleep_for(_frequencyNs - (end - start));
			}
		}

		void Clock::stop()
		{
			_running.fetch_and_store(false);
		}
	}
}