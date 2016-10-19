#include "NL_Scene.h"
#include "NL_Uuid.h"
#include "NL_ThreadLocal.h"
#include "NL_GameObject.h"
#include "NL_GameManager.h"

namespace NLE
{
	namespace GAME
	{
		Scene::Scene() : Scene(nullptr) {}

		Scene::Scene(GameManager* gameManager) :
			_gameManager(gameManager),
			_uuid(UUID::generateUuid()),
			_scriptingContext(this)
		{
			_name = L"Scene " + std::to_wstring(_uuid);
		}

		Scene::~Scene()
		{

		}

		GameManager* Scene::getGameManager()
		{
			return _gameManager;
		}

		void Scene::setGameManager(GameManager& gameManager)
		{
			_gameManager = &gameManager;
		}

		std::wstring Scene::getName()
		{
			return _name;
		}

		void Scene::setName(std::wstring name)
		{
			_name = name;
		}

		void Scene::addObject(GameObject* object)
		{
			_objects.insert(object->getUuid(), object);
		}

		GameObject* Scene::getObject(unsigned long long uuid)
		{
			GameObject* object = nullptr;
			_objects.get(uuid, object);
			return object;
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