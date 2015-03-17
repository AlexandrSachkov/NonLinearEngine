#include "NL_Clock.h"

namespace NLE
{
	namespace Core
	{
		Clock::Clock()
		{

		}

		Clock::~Clock()
		{

		}

		bool Clock::initialize()
		{
			return true;
		}

		void Clock::release()
		{

		}

		void Clock::run()
		{

		}

		void Clock::stop()
		{

		}

		void Clock::onTick(std::function<void()> operation)
		{
			operation();
		}
	}
}