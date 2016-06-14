#ifndef NL_IGAME_MANAGER_H_
#define NL_IGAME_MANAGER_H_

#include <string>

namespace NLE
{
	namespace GAME
	{
		class Game;
		class Scene;
		class GameObject;
		namespace COMMAND
		{
			enum Type
			{
				QUIT_GAME,
				RESTART_GAME,
				LOAD_GAME,
				UPDATE_GAME,
				LOAD_SCENE,
				UPDATE_SCENE,
				SAVE_GAME,
				SAVE_SCENE,
				ADD_OBJECT,
				UPDATE_OBJECT,
				LOAD_OBJECT,
				SAVE_OBJECT,
			};

			union Data
			{
				Data() : name(nullptr), game(nullptr), scene(nullptr) {}
				char* name;
				Game* game;
				Scene* scene;
				GameObject* gameObject;
			};
		}

		class IGameManager
		{
		public:
			virtual void queueCommand(COMMAND::Type type, COMMAND::Data data) = 0;
		};
	}
}

#endif