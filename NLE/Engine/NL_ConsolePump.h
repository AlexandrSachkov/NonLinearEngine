#ifndef NL_CONSOLE_PUMP_H_
#define NL_CONSOLE_PUMP_H_

#include "NLCore\NL_System.h"
#include "NL_IConsolePump.h"

namespace NLE
{
	namespace Core
	{
		class IEngine;
		class ISystem;
	}

	namespace CONSOLE
	{
		class ConsolePump : public Core::System, public Core::ISystem
		{
		public:
			ConsolePump();
			~ConsolePump();

			bool initialize(Core::IEngine& engine);
			void release();

			bool initialized();

			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();

		private:
			bool _initialized;
			std::function<void()> _procedure;
			void(*_printConsole)(OUTPUT_TYPE, const char*);
		};
	}
}

#endif
