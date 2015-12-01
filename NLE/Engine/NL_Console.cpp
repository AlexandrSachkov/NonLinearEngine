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

		void Console::queueData(OUTPUT_TYPE outType, const std::wstring& data)
		{
			_dataQueue.push({ outType, data });
		}

		bool Console::pullData(std::pair<OUTPUT_TYPE, std::wstring>& data)
		{
			if (_dataQueue.try_pop(data))
				return true;
			return false;
		}
	}
}
