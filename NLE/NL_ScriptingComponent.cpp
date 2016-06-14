#include "NL_ScriptingComponent.h"

namespace NLE
{
	namespace GAME
	{
		ScriptingComponent::ScriptingComponent()
		{

		}

		ScriptingComponent::~ScriptingComponent()
		{

		}

		SCRIPT::ScriptingContext& ScriptingComponent::getScriptingContext()
		{
			return _scriptingContext;
		}
	}
}