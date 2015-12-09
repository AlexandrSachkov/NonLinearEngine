#ifndef NL_SCRIPT_EXECUTOR_H_
#define NL_SCRIPT_EXECUTOR_H_

#include "lua.hpp"

namespace NLE
{
	namespace SCRIPT
	{
		class ScriptExecutor
		{
		public:
			ScriptExecutor();
			~ScriptExecutor();

			lua_State* getState();
			bool executeScript(const char* script);

		private:
			lua_State* _state;

		};
	}
}

#endif