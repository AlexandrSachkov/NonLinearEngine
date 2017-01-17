#pragma once

#include "cereal\cereal.hpp"

namespace NLE
{
	namespace GAME
	{
		class GameObject;
		class GameObjectComponent
		{
		public:
			GameObjectComponent(GameObject* parent);
			~GameObjectComponent();

			template<class Archive>
			void save(Archive& archive) const
			{
				archive(CEREAL_NVP(_enabled));
			}

			template<class Archive>
			void load(Archive& archive)
			{
				archive(CEREAL_NVP(_enabled));
			}

			GameObject* getParent();
			void setEnabled(bool enabled);
			bool getEnabled();

		private:
			GameObject* _parent;
			bool _enabled;
		};
	}
}
