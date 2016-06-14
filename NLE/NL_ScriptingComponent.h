#ifndef NL_SCRIPTING_COMPONENT_H_
#define NL_SCRIPTING_COMPONENT_H_

#include "NL_GameObjectComponent.h"
#include "NL_ScriptingContext.h"

namespace NLE
{
	namespace GAME
	{
		class ScriptingComponent : public GameObjectComponent
		{
		public:
			ScriptingComponent(GameObject* parent);
			~ScriptingComponent();

			SCRIPT::ScriptingContext& getScriptingContext();

		private:
			SCRIPT::ScriptingContext _scriptingContext;
		};
	}
}

#endif
