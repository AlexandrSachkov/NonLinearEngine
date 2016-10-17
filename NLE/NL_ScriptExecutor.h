#ifndef NL_SCRIPT_EXECUTOR_H_
#define NL_SCRIPT_EXECUTOR_H_

#include "lua.hpp"
#include <string>

namespace NLE
{
	namespace SCRIPT
	{
		class ScriptingContext;
		class ScriptExecutor
		{
		public:
			ScriptExecutor();
			~ScriptExecutor();

			lua_State* getState();
			void registerCallback(std::wstring name, int(*callback)(lua_State* state));
			std::wstring getExecutionError();
			bool executeContextScript(ScriptingContext& context, std::wstring name);
			bool executeScript(std::wstring script);

		private:
			lua_State* _state;
			std::wstring _executionError;
		};
	}
}

#endif