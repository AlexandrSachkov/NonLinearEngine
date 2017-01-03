#ifndef NL_GAME_OBJECT_H_
#define NL_GAME_OBJECT_H_

#include "NL_ThreadLocal.h"
#include "NL_IScriptable.h"
#include "NL_RenderingComponent.h"
#include "NL_ScriptingComponent.h"
#include <string>

namespace NLE
{
	namespace GAME
	{
		class Scene;
		class RenderingComponent;
		class ScriptingComponent;
		class GameObject
		{
		public:
			GameObject();
			~GameObject();

			template<class Archive>
			void save(Archive& archive) const
			{
				auto& cnv = TLS::strConverter.local();
				auto name = cnv.to_bytes(_name);
				archive(
					CEREAL_NVP(name),
					CEREAL_NVP(_scriptingComponent),
					CEREAL_NVP(_renderingComponent)
					);
			}

			template<class Archive>
			void load(Archive& archive)
			{
				auto& cnv = TLS::strConverter.local();
				std::string name;
				archive(
					CEREAL_NVP(name),
					CEREAL_NVP(_scriptingComponent),
					CEREAL_NVP(_renderingComponent)
					);

				_name = cnv.from_bytes(name);
			}

			static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
			{
				binding.beginClass<GameObject>("GameObject")
					.addProperty("name", &GameObject::getName, &GameObject::setName)
					.addFunction("getParent", &GameObject::getParent)
					.addFunction("getChildren", &GameObject::getChildren)
					.addFunction("getScriptingContext", &GameObject::getScriptingContext)
					.endClass();
			}

			void setName(std::wstring name);
			std::wstring getName();

			void setParent(GameObject* obj);
			GameObject* getParent();
			void addChild(GameObject* obj);
			void removeChild(GameObject* obj);
			const std::vector<GameObject*>& getChildren();

			RenderingComponent& getRenderingComponent();
			ScriptingComponent& getScriptingComponent();
			SCRIPT::ScriptingContext& getScriptingContext();

		private:
			ScriptingComponent _scriptingComponent;
			RenderingComponent _renderingComponent;			

			std::wstring _name;
			GameObject* _parent;
			std::vector<GameObject*> _children;
		};
	}
}

#endif
