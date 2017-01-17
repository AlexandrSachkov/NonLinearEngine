#pragma once

#include "NL_GameObjectComponent.h"

#include "cereal\cereal.hpp"
#include <cereal/types/base_class.hpp>

namespace NLE
{
	namespace GAME
	{
		class RenderingComponent : public GameObjectComponent
		{
		public:
			RenderingComponent(GameObject* parent);
			~RenderingComponent();

			template<class Archive>
			void save(Archive& archive) const
			{
				archive(
					cereal::base_class<GameObjectComponent>(this)
					);
			}

			template<class Archive>
			void load(Archive& archive)
			{
				archive(
					cereal::base_class<GameObjectComponent>(this)
					);
			}
		};
	}
}