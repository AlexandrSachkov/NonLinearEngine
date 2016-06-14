#ifndef NL_GAME_OBJECT_COMPONENT_H_
#define NL_GAME_OBJECT_COMPONENT_H_

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
			GameObject* getParent();

		private:
			GameObject* _parent;
		};
	}
}

#endif