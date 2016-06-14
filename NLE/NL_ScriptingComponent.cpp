#include "NL_ScriptingComponent.h"

namespace NLE
{
	namespace GAME
	{
		ScriptingComponent::ScriptingComponent(GameObject* parent) :
			GameObjectComponent(parent)
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