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
			void registerCallback(std::string name, int(*callback)(lua_State* state));
			std::string getExecutionError();
			bool executeContextScript(ScriptingContext& context, std::string name);
			bool executeScript(std::string script);

		private:
			void applyContext(ScriptingContext& context);
			lua_State* _state;
			std::string _executionError;
		};
	}
}

#endif