#include "NL_Console.h"

namespace NLE
{
	namespace CONSOLE
	{
		Console* Console::_console = nullptr;

		Console::Console()
		{
		}

		Console::~Console()
		{
		}

		void Console::release()
		{
			delete this;
		}

		void Console::queueData(OUTPUT_TYPE outType, const std::wstring& data)
		{
			_dataQueue.push({ outType, data });
		}

		void Console::attachPrintConsole(void(*printConsole)(OUTPUT_TYPE, const char*))
		{
			_printConsole = printConsole;
		}

		void Console::outputConsole()
		{
			TLS::StringConverter::reference converter = TLS::strConverter.local();

			std::pair<OUTPUT_TYPE, std::wstring> data;
			while (_dataQueue.try_pop(data))
			{
				_printConsole(data.first, converter.to_bytes(data.second).c_str());
			}
		}
	}
}
