#ifndef NL_IGAME_MANAGER_H_
#define NL_IGAME_MANAGER_H_

#include "NL_ISystem.h"
#include <string>
#include <memory>

namespace NLE
{
	namespace GAME
	{
		enum ExecStatus
		{
			CONTINUE,
			TERMINATE,
			RESTART
		};

		class Game;
		class Scene;
		class IGameManager : public ISystem
		{
		public:
			virtual ExecStatus getExecutionStatus() = 0;
			virtual bool hasUnsavedChanges() = 0;
			virtual void newGame() = 0;
			virtual void newScene() = 0;
			virtual void loadGame(std::string path) = 0;
			virtual void loadScene(std::string path) = 0;
			virtual void loadSceneByName(std::string name) = 0;
			virtual void saveGame(std::string name) = 0;
			virtual void saveScene(std::string name) = 0;
			virtual void quitGame() = 0;

			virtual Game& getGame() = 0;
			virtual Scene& getCurrentScene() = 0;

			virtual ~IGameManager() {}
		};

		typedef std::shared_ptr<IGameManager> IGameManagerSP;
	}
}

#endif