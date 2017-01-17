#pragma once

#include "NL_GameObjectComponent.h"
#include "NL_ScriptingContext.h"
#include "NL_IScriptable.h"

#include "cereal/cereal.hpp"
#include <cereal/types/base_class.hpp>

namespace NLE
{
	namespace GAME
	{
		class ScriptingComponent : public GameObjectComponent, public SCRIPT::IScriptable
		{
		public:
			ScriptingComponent(GameObject* parent);
			~ScriptingComponent();

			template<class Archive>
			void save(Archive& archive) const
			{
				archive(
					cereal::base_class<GameObjectComponent>(this),
					CEREAL_NVP(_scriptingContext)
					);
			}

			template<class Archive>
			void load(Archive& archive)
			{
				archive(
					cereal::base_class<GameObjectComponent>(this),
					CEREAL_NVP(_scriptingContext)
					);
			}

			SCRIPT::ScriptingContext& getScriptingContext();
			void bind(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding);

		private:
			SCRIPT::ScriptingContext _scriptingContext;
		};
	}
}
