#pragma once

#include "NL_ScriptingContext.h"
#include "NL_IScriptable.h"
#include "NL_Map.h"
#include "NL_LuaCustomTypes.h"
#include "NL_SceneGraph.h"

#include <string>
#include "NL_ThreadLocal.h"
#include <memory>

namespace NLE
{
	namespace GAME
	{
		class GameObject;
		class GameManager;
		class Scene : public SCRIPT::IScriptable
		{
		public:
			Scene();
			~Scene();

			template<class Archive>
			void save(Archive& archive) const
			{
				archive(
					CEREAL_NVP(_name),
					CEREAL_NVP(_sceneGraph),
					CEREAL_NVP(_scriptingContext)
					);
			}

			template<class Archive>
			void load(Archive& archive)
			{
				archive(
					CEREAL_NVP(_name),
					CEREAL_NVP(_sceneGraph),
					CEREAL_NVP(_scriptingContext)
					);

				_scriptingContext.setParent(this);
			}

			std::string getName();
			void setName(std::string name);

			void addObject(GameObject* object);
			void addObject(GameObject* parent, GameObject* object);
			void removeObject(std::string name);
			void removeObject(GameObject* object);
			GameObject* getObject(std::string name);

			SCRIPT::ScriptingContext& getScriptingContext();
			void bind(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding);

			static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<Scene>("Scene")
					.addFunction("getName", &Scene::getName)
					.addFunction("getObject", &Scene::getObject)
					.endClass();
			}
			static void attachMasterBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<Scene>("Scene")
					.addFunction("setName", &Scene::setName)
					//.addFunction("addObject", static_cast<void(Scene::*)(std::wstring name, double data)>(&Scene::addObject))
					//.addFunction("addObject", &Scene::setName)
					.endClass();
			}

		private:
			std::string _name;
			SceneGraph _sceneGraph;
			SCRIPT::ScriptingContext _scriptingContext;
		};

		typedef std::unique_ptr<Scene> SceneUP;
	}
}