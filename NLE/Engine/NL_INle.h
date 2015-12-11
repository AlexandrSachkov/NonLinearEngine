#ifndef NL_IENGINE_H_
#define NL_IENGINE_H_

#include "NL_ConsoleOutType.h"
#include <cstdint>

struct lua_State;
namespace NLE
{
	namespace INPUT
	{
		struct Event;
	}
	class INle
	{
	public:
		virtual bool initialize() = 0;
		virtual void release() = 0;

		virtual void run() = 0;
		virtual void stop() = 0;

		virtual void attachPollEvents(void(*pollEvents)(void)) = 0;
		virtual void attachPrintConsole(void(*printConsole)(CONSOLE::OUTPUT_TYPE, const char*)) = 0;
		virtual void processEvent(INPUT::Event& event) = 0;
		virtual void setWindowHandle(void* handle) = 0;

		virtual void bindScriptCallback(const char* name, int(*)(lua_State* state)) = 0;
		virtual void executeScript(const char* script) = 0;
	};
}
#endif