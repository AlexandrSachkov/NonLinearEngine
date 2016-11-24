#include "NL_GameObject.h"
#include "NL_Uuid.h"
#include "NL_Scene.h"

namespace NLE
{
	namespace GAME
	{
		GameObject::GameObject() :
			_name(L"Object " + std::to_wstring(UUID::generateUuid())),
			_parent(nullptr),
			_renderingComponent(this),
			_scriptingComponent(this)
		{
		}

		GameObject::~GameObject()
		{

		}

		void GameObject::setScene(Scene* scene)
		{
			_scene = scene;
		}

		Scene* GameObject::getScene()
		{
			return _scene;
		}

		std::wstring GameObject::getName()
		{
			return _name;
		}

		void GameObject::setName(std::wstring name)
		{
			_name = name;
		}

		void GameObject::setParent(GameObject* obj)
		{
			_parent = obj;
		}

		GameObject* GameObject::getParent()
		{
			return _parent;
		}

		void GameObject::addChild(GameObject* obj)
		{
			for (auto it = _children.begin(); it != _children.end(); ++it)
			{
				if ((*it) == obj)
				{
					return;
				}
			}
			_children.push_back(obj);
		}

		void GameObject::removeChild(GameObject* obj)
		{
			for (auto it = _children.begin(); it != _children.end(); ++it)
			{
				if ((*it) == obj)
				{
					_children.erase(it);
				}
			}
		}

		const std::vector<GameObject*>& GameObject::getChildren()
		{
			return _children;
		}

		RenderingComponent& GameObject::getRenderingComponent()
		{
			return _renderingComponent;
		}

		ScriptingComponent& GameObject::getScriptingComponent()
		{
			return _scriptingComponent;
		}

		SCRIPT::ScriptingContext& GameObject::getScriptingContext()
		{
			return _scriptingComponent.getScriptingContext();
		}
	}
}