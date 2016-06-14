#include "NL_ConsoleQueue.h"

namespace NLE
{
	namespace CONSOLE
	{
		ConsoleQueue::ConsoleQueue()
		{
		}

		ConsoleQueue::~ConsoleQueue()
		{
		}

		void ConsoleQueue::push(OUTPUT_TYPE outType, const std::wstring& data)
		{
			_data.push({ outType, data });
		}

		void ConsoleQueue::push(OUTPUT_TYPE outType, const std::string& data)
		{
			TLS::StringConverter::reference converter = TLS::strConverter.local();
			_data.push({ outType, converter.from_bytes(data) });
		}

		void ConsoleQueue::push(OUTPUT_TYPE outType, const char* data)
		{
			TLS::StringConverter::reference converter = TLS::strConverter.local();
			_data.push({ outType, converter.from_bytes(data) });
		}

		bool ConsoleQueue::pop(std::pair<OUTPUT_TYPE, std::wstring>& data)
		{
			if (_data.empty())
				return false;

			return _data.try_pop(data);
		}

		void ConsoleQueue::clear()
		{
			_data.clear();
		}
	}

}
