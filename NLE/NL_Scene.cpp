#include "NL_Scene.h"
#include "NL_Uuid.h"
#include "NL_ThreadLocal.h"
#include "NL_GameObject.h"
#include "NL_GameManager.h"

namespace NLE
{
	namespace GAME
	{
		Scene::Scene(const SceneDesc& desc) :
			_name(desc.name),
			_scriptingContext(desc.scriptingContextDesc)
		{

		}

		Scene::Scene(const Scene& other) :
			_name(other._name),
			_scriptingContext(other._scriptingContext)
		{
		}

		Scene& Scene::operator=(const Scene& other)
		{
			_name = other._name;
			_scriptingContext = other._scriptingContext;
			return *this;
		}

		Scene::~Scene()
		{
		}

		SceneDesc Scene::getDesc()
		{
			SceneDesc desc;
			desc.name = _name;
			desc.scriptingContextDesc = _scriptingContext.getDesc();
			return desc;
		}

		std::string Scene::getName()
		{
			return _name;
		}

		void Scene::setName(std::string name)
		{
			_name = name;
		}

		void Scene::addObject(GameObject* object)
		{
			_sceneGraph.addObject(object);
		}

		void Scene::addObject(GameObject* parent, GameObject* object)
		{
			_sceneGraph.addObject(parent, object);
		}

		void Scene::removeObject(std::string name)
		{
			_sceneGraph.removeObject(name);
		}

		void Scene::removeObject(GameObject* object)
		{
			_sceneGraph.removeObject(object);
		}

		GameObject* Scene::getObject(std::string name)
		{
			return _sceneGraph.getObject(name);
		}

		SCRIPT::ScriptingContext& Scene::getScriptingContext()
		{
			return _scriptingContext;
		}

		void Scene::bind(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
		{
			binding.addVariableRef<Scene>("this", this);
		}
	}
}