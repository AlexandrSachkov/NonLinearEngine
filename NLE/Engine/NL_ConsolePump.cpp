#include "NL_ConsolePump.h"
#include "NL_Console.h"
#include "NL_ThreadLocal.h"

#include <assert.h>

namespace NLE
{
	namespace CONSOLE
	{
		ConsolePump::ConsolePump() :
			_initialized(false)
		{
		}

		ConsolePump::~ConsolePump()
		{
		}

		bool ConsolePump::initialize(Core::IEngine& engine)
		{
			assert(!_initialized && _printConsole);

			_initialized = true;
			return _initialized;
		}

		void ConsolePump::release()
		{
			_initialized = false;
		}

		bool ConsolePump::initialized()
		{
			return _initialized;
		}

		std::function<void()> const& ConsolePump::getExecutionProcedure()
		{
			_procedure = [&]() {
				TLS::StringConverter::reference converter = TLS::strConverter.local();

				std::pair<OUTPUT_TYPE, std::wstring> data;
				while (Console::instance().pullData(data))
				{
					_printConsole(data.first, converter.to_bytes(data.second).c_str());
				}
			};

			return _procedure;
		}

		Core::ISystem& ConsolePump::getInterface()
		{
			return *this;
		}

		void ConsolePump::attachPrintConsole(void(*printConsole)(OUTPUT_TYPE, const char*))
		{
			assert(!_initialized);
			_printConsole = printConsole;
		}
	}
}