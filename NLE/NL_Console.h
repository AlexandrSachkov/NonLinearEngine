#ifndef NL_CONSOLE_H_
#define NL_CONSOLE_H_

#include "NL_ThreadLocal.h"

#include "tbb\concurrent_queue.h"

#include <functional>

#if defined(DEBUG) || defined(_DEBUG)
#define CONSOLE_DEBUG(data) do { NLE::CONSOLE::out(NLE::CONSOLE::DEBUG, data); } while( false )
#else
#define CONSOLE_DEBUG(data) do { } while ( false )
#endif

namespace NLE
{
	namespace CONSOLE
	{
		enum OUTPUT_TYPE
		{
			DEBUG,
			STANDARD,
			WARNING,
			ERR
		};

		class Console
		{
		public:
			static Console& instance()
			{
				if (!_console)
				{
					_console = new Console();
				}
				return *_console;
			};

			~Console();
			void release();
			void queueData(OUTPUT_TYPE outType, const std::wstring& data);
			void outputConsole();
			void attachPrintConsole(void(*printConsole)(OUTPUT_TYPE, const char*));

		private:
			Console();
			Console(Console const&) = delete;
			void operator=(Console const&) = delete;		

			static Console* _console;
			tbb::concurrent_queue <std::pair<OUTPUT_TYPE, std::wstring>> _dataQueue;
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> _converter;
			std::function<void(OUTPUT_TYPE, const char*)> _printConsole;
		};
		
		static void out(OUTPUT_TYPE outType, const std::wstring& data)
		{
			Console::instance().queueData(outType, data);
		}

		static void out(OUTPUT_TYPE outType, const std::string& data)
		{
			TLS::StringConverter::reference converter = TLS::strConverter.local();
			Console::instance().queueData(outType, converter.from_bytes(data));
		}

		static void out(OUTPUT_TYPE outType, const char* data)
		{
			TLS::StringConverter::reference converter = TLS::strConverter.local();
			Console::instance().queueData(outType, converter.from_bytes(data));
		}
	}

}

#endif
