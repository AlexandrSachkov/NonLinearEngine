#pragma once

#include "NL_ThreadLocal.h"
#include "NL_IConsoleQueue.h"
#include "NL_Globals.h"
#include "NL_LuaCustomTypes.h"

#include "tbb\concurrent_queue.h"
#include <LuaIntf.h>

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

			void push(OUTPUT_TYPE outType, const std::string& data);
			void push(OUTPUT_TYPE outType, const char* data);

			bool pop(std::pair<OUTPUT_TYPE, std::string>& data);
			void clear();
		private:
			tbb::concurrent_queue <std::pair<OUTPUT_TYPE, std::string>> _data;
		};

		static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
		{
			binding.beginModule("console")
				.addFunction("print", [](std::string data) {
					CONSOLE::GLOBAL_CONSOLE_QUEUE->push(CONSOLE::STANDARD, data);
				})
			.endModule();
		}
	}

}

