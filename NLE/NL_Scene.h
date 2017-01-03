#ifndef NL_SCENE_H_
#define NL_SCENE_H_

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
			Scene(GameManager* _gameManager);
			~Scene();

			template<class Archive>
			void save(Archive& archive) const
			{
				auto& cnv = TLS::strConverter.local();
				auto name = cnv.to_bytes(_name);
				archive(
					CEREAL_NVP(name),
					CEREAL_NVP(_sceneGraph),
					CEREAL_NVP(_scriptingContext)
					);
			}

			template<class Archive>
			void load(Archive& archive)
			{
				auto& cnv = TLS::strConverter.local();
				std::string name;
				archive(
					CEREAL_NVP(name),
					CEREAL_NVP(_sceneGraph),
					CEREAL_NVP(_scriptingContext)
					);

				_scriptingContext.setParent(this);
				_name = cnv.from_bytes(name);
			}

			GameManager* getGameManager();
			void setGameManager(GameManager& gameManager);

			std::wstring getName();
			void setName(std::wstring name);

			void addObject(GameObject* object);
			void addObject(GameObject* parent, GameObject* object);
			void removeObject(std::wstring name);
			void removeObject(GameObject* object);
			GameObject* getObject(std::wstring name);

			SCRIPT::ScriptingContext& getScriptingContext();
			void bind(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding);

			static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<Scene>("Scene")
					.addFunction("getGameManager", &Scene::getGameManager)
					.addFunction("getName", &Scene::getName)
					.addFunction("getObject", &Scene::getObject)
					.endClass();
			}

		private:
			GameManager* _gameManager;
			std::wstring _name;
			SceneGraph _sceneGraph;
			SCRIPT::ScriptingContext _scriptingContext;
		};

		typedef std::unique_ptr<Scene> SceneUP;
	}
}
#endif