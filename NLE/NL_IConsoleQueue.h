#ifndef NL_I_CONSOLE_QUEUE_H_
#define NL_I_CONSOLE_QUEUE_H_

#include <string>

namespace NLE
{
#if defined(DEBUG) || defined(_DEBUG)
#define CONSOLE_DEBUG(queue, data) queue.push(NLE::OUTPUT_TYPE::DEBUG, data);
#else
#define CONSOLE_DEBUG(queue, data)
#endif

#if defined(DEBUG) || defined(_DEBUG) || defined(NL_ENABLE_WARNINGS)
#define CONSOLE_WARN(queue, data) queue.push(NLE::OUTPUT_TYPE::WARNING, data);
#else
#define CONSOLE_WARN(queue, data)
#endif
	namespace CONSOLE
	{
		enum OUTPUT_TYPE
		{
			DEBUG,
			STANDARD,
			WARNING,
			ERR
		};

		class IConsoleQueue
		{
		public:
			virtual void push(OUTPUT_TYPE outType, const std::wstring& data) = 0;
			virtual void push(OUTPUT_TYPE outType, const std::string& data) = 0;
			virtual void push(OUTPUT_TYPE outType, const char* data) = 0;
		};
	}

}

#endif