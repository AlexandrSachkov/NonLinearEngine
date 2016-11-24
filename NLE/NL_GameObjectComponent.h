#ifndef NL_GAME_OBJECT_COMPONENT_H_
#define NL_GAME_OBJECT_COMPONENT_H_

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

#endif