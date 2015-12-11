#ifndef NL_I_UI_MANAGER_H_
#define NL_I_UI_MANAGER_H_

#include "NLCore\NL_ISystem.h"

struct lua_State;
namespace NLE
{
	namespace UI
	{
		class IUiManager : public Core::ISystem
		{
		public:
			virtual bool initialized() = 0;

			virtual void bindScriptCallback(const char* name, int(*)(lua_State* state), bool async) = 0;
			virtual void executeScript(const char* script, bool async) = 0;
		};
	}
}

#endif
