#ifndef NL_CONSOLE_QUEUE_H_
#define NL_CONSOLE_QUEUE_H_

#include "NL_ThreadLocal.h"
#include "NL_IConsoleQueue.h"
#include "tbb\concurrent_queue.h"
#include <functional>

namespace NLE
{
	namespace CONSOLE
	{
		class ConsoleQueue : public IConsoleQueue
		{
		public:
			ConsoleQueue();
			~ConsoleQueue();

			void push(OUTPUT_TYPE outType, const std::wstring& data);
			void push(OUTPUT_TYPE outType, const std::string& data);
			void push(OUTPUT_TYPE outType, const char* data);

			bool pop(std::pair<OUTPUT_TYPE, std::wstring>& data);

		private:
			tbb::concurrent_queue <std::pair<OUTPUT_TYPE, std::wstring>> _data;
		};
	}

}

#endif
