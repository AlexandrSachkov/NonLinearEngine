#ifndef NL_IGAME_MANAGER_H_
#define NL_IGAME_MANAGER_H_

#include <string>

namespace NLE
{
	namespace GAME
	{
		class IGameManager
		{
		public:
			virtual void loadGame(std::wstring game) = 0;
			virtual void saveGame() = 0;
			virtual void quitGame() = 0;
			virtual void restartGame() = 0;

			virtual void loadScene(std::wstring scene) = 0;

			virtual void loadGameObject(std::wstring gameObject) = 0;
			virtual void unloadGameObject(std::wstring gameObject) = 0;

			virtual void importMesh(std::wstring mesh) = 0;
		};
	}
}

#endif