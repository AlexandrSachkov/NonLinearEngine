#ifndef NL_CLOCK_H_
#define NL_CLOCK_H_

#include <functional>

namespace NLE
{
	namespace Core
	{
		class Clock
		{
		public:
			Clock();
			~Clock();

			bool initialize();
			void release();

			void run();
			void stop();

			void onTick(std::function<void()> operation);
			
		private:
			
		};
	}
}


#endif