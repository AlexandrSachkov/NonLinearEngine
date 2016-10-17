#ifndef NL_SCRIPTING_COMPONENT_H_
#define NL_SCRIPTING_COMPONENT_H_

#include "NL_GameObjectComponent.h"
#include "NL_ScriptingContext.h"
#include "NL_IScriptable.h"

namespace NLE
{
	namespace GAME
	{
		class ScriptingComponent : public GameObjectComponent, public SCRIPT::IScriptable
		{
		public:
			ScriptingComponent(GameObject* parent);
			~ScriptingComponent();

			SCRIPT::ScriptingContext& getScriptingContext();
			void bind(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding);

		private:
			SCRIPT::ScriptingContext _scriptingContext;
		};
	}
}

#endif
