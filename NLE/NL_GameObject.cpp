#include "NL_GameObject.h"
#include "NL_RenderingComponent.h"
#include "NL_UiComponent.h"
#include "NL_ScriptingComponent.h"
#include "NL_Uuid.h"

namespace NLE
{
	namespace GAME
	{
		GameObject::GameObject() :
			_uuid(UUID::generateUuid())
		{
			_renderingComponent = nullptr;
			_uiComponent = nullptr;
			_scriptingComponent = nullptr;

			_name = L"Object " + std::to_wstring(_uuid);
		}

		GameObject::~GameObject()
		{

		}

		unsigned long long GameObject::getUuid()
		{
			return _uuid;
		}

		std::wstring GameObject::getName()
		{
			return _name;
		}
	}
}