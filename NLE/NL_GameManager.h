#ifndef NL_GAME_MANAGER_H_
#define NL_GAME_MANAGER_H_

#include "NL_IGameManager.h"

#include <functional>

#include "tbb\atomic.h"

namespace NLE
{
	namespace GRAPHICS
	{
		class Scene;
	}

	class GameManager : public IGameManager
	{
	public:
		GameManager();
		~GameManager();

		bool initialize();
		void update();

	private:

	};
}


#endif