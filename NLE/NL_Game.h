#ifndef NL_GAME_H_
#define NL_GAME_H_

#include <string>

namespace NLE
{
	class Game
	{
	public:
		Game();
		~Game();

		static Game* load(std::wstring path);
	private:
	};
}

#endif