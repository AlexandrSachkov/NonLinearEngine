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
			GameObject* child = nullptr;
			if (_childMap.get(obj->getName(), child))
				return;

			_childMap.insert(obj->getName(), obj);
			_children.push_back(obj);
			_dependencies.push_back(obj->getName());
		}

		void GameObject::removeChild(std::wstring name)
		{
			if (!_childMap.erase(name))
				return;

			for (auto it = _children.begin(); it != _children.end(); ++it)
			{
				if ((*it)->getName().compare(name) == 0)
				{
					_children.erase(it);
				}
			}

			for (auto it = _dependencies.begin(); it != _dependencies.end(); ++it)
			{
				if ((*it).compare(name) == 0)
				{
					_dependencies.erase(it);
				}
			}
		}

		GameObject* GameObject::getChild(std::wstring name)
		{
			GameObject* child = nullptr;
			_childMap.get(name, child);
			return child;
		}

		const std::vector<GameObject*>& GameObject::getChildren()
		{
			return _children;
		}

		const std::vector<std::wstring>& GameObject::getDependencies()
		{
			return _dependencies;
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