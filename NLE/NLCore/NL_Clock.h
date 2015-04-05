#ifndef NL_CLOCK_H_
#define NL_CLOCK_H_

#include <functional>
#include "tbb\atomic.h"
#include <chrono>

namespace NLE
{
	namespace Core
	{
		class Clock
		{
		public:
			Clock();
			~Clock();

			bool initialize(std::function<void()> operation);
			void release();

			void setFrequencyNs(unsigned long long frequencyNs);
			void run();
			void stop();
			
		private:
			tbb::atomic<bool> _running;
			std::chrono::duration<unsigned long long, std::nano> _frequencyNs;
			std::function<void()> _operation;
		};
	}
}


#endif