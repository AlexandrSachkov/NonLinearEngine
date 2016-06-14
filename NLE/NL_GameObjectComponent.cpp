#include "NL_GameObjectComponent.h"
#include "NL_GameObject.h"

namespace NLE
{
	namespace GAME
	{
		GameObjectComponent::GameObjectComponent(GameObject* parent) :
			_parent(parent)
		{
		}

		GameObjectComponent::~GameObjectComponent()
		{
		}

		GameObject* GameObjectComponent::getParent()
		{
			return _parent;
		}
	}
}