#ifndef NL_IGAME_MANAGER_H_
#define NL_IGAME_MANAGER_H_

#include <string>

namespace NLE
{
	namespace GAME
	{
		class Game;
		class Scene;
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
				SAVE_SCENE
			};

			union Data
			{
				Data() : name(nullptr), game(nullptr), scene(nullptr) {}
				char* name;
				Game* game;
				Scene* scene;
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