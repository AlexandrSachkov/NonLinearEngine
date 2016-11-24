#include "NL_GameObjectComponent.h"
#include "NL_GameObject.h"

namespace NLE
{
	namespace GAME
	{
		GameObjectComponent::GameObjectComponent(GameObject* parent) :
			_parent(parent),
			_enabled(false)
		{
		}

		GameObjectComponent::~GameObjectComponent()
		{
		}

		GameObject* GameObjectComponent::getParent()
		{
			return _parent;
		}

		void GameObjectComponent::setEnabled(bool enabled)
		{
			_enabled = enabled;
		}

		bool GameObjectComponent::getEnabled()
		{
			return _enabled;
		}
	}
}