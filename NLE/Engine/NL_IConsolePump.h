#ifndef NL_I_CONSOLE_PUMP_H_
#define NL_I_CONSOLE_PUMP_H_

#include "NLCore\NL_ISystem.h"
#include "NL_ConsoleOutType.h"

namespace NLE
{
	namespace CONSOLE
	{
		class IConsolePump : public Core::ISystem
		{
		public:
			virtual void attachPrintConsole(void(*printConsole)(OUTPUT_TYPE, const char*)) = 0;
		};
	}
}

#endif
