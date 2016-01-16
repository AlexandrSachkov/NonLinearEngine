#ifndef NL_UI_MANAGER_H_
#define NL_UI_MANAGER_H_

#include "NL_IUiManager.h"
#include "NL_System.h"
#include "NL_Console.h"

#include "tbb\concurrent_queue.h"

namespace NLE
{
	namespace Core
	{
		class IEngine;
		class ISystem;
		struct SysInitializer;
	}

	namespace UI
	{
		class UiManager : public Core::System, public IUiManager
		{
		public:
			UiManager();
			~UiManager();

			bool initialize(std::unique_ptr<Core::SysInitializer> const& initializer);
			void start();
			void stop();
			void release();

			bool initialized();

			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();		
			
			void bindScriptCallback(const char* name, int(*)(lua_State* state), bool async);
			void executeScript(const char* script, bool async);

		private:			
			int getData(lua_State* state);
			int setData(lua_State* state);
			static int uiGetData(lua_State* state);
			static int uiSetData(lua_State* state);

			bool _initialized;
			std::function<void()> _procedure;
			void(*_printConsole)(CONSOLE::OUTPUT_TYPE, const char*);

			tbb::concurrent_queue<std::string> _scripts;
			tbb::concurrent_queue<std::pair<std::string, int(*)(lua_State* state)>> _callbacks;
		};
	}
}

#endif
