#include "NL_ScriptingComponent.h"

namespace NLE
{
	namespace GAME
	{
		ScriptingComponent::ScriptingComponent(GameObject* parent) :
			GameObjectComponent(parent),
			_scriptingContext(SCRIPT::ScriptingContextDesc())
		{

		}

		ScriptingComponent::~ScriptingComponent()
		{

		}

		SCRIPT::ScriptingContext& ScriptingComponent::getScriptingContext()
		{
			return _scriptingContext;
		}

		void ScriptingComponent::bind(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
		{
			binding.addVariableRef<GameObject>("this", getParent());
		}
	}
}