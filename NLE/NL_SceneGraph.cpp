#include "NL_SceneGraph.h"
#include "NL_GameObject.h"

namespace NLE
{
	namespace GAME
	{
		SceneGraph::SceneGraph()
		{

		}

		SceneGraph::~SceneGraph()
		{

		}

		void SceneGraph::addObject(GameObject* object)
		{
			//addObject(nullptr, object);
		}

		void SceneGraph::addObject(GameObject* parent, GameObject* object)
		{
			/*_objects.insert({ object->getName(), object });

			if (!parent)
			{
				_root.push_back(object);
			}
			else
			{
				if (object->getParent())
				{
					object->getParent()->removeChild(object);
				}
				parent->addChild(object);
			}*/
		}

		void SceneGraph::removeObject(std::string name)
		{
			/*GameObject* obj = nullptr;
			_objects.
			if (_objects.get(name, obj))
			{
				removeObject(obj);
			}*/
		}

		void SceneGraph::removeObject(GameObject* object)
		{
			/*if (object->getParent())
			{
				object->getParent()->removeChild(object);
			}
			_objects.erase(object->getName());*/
		}

		GameObject* SceneGraph::getObject(std::string name)
		{
			/*GameObject* obj = nullptr;
			_objects.get(name, obj);
			return obj;*/
			return nullptr;
		}
	}
}