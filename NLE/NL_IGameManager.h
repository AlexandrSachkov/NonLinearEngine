#ifndef NL_IGAME_MANAGER_H_
#define NL_IGAME_MANAGER_H_

#include "NL_ISystem.h"
#include <string>

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
			virtual void loadGame(std::wstring path) = 0;
			virtual void loadScene(std::wstring path) = 0;
			virtual void saveGame(std::wstring name) = 0;
			virtual void saveScene(std::wstring name) = 0;
			virtual void quitGame() = 0;

			virtual Game& getGame() = 0;
			virtual Scene& getCurrentScene() = 0;

			virtual ~IGameManager() {}
		};
	}
}

#endif