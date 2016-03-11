#ifndef NL_GAME_H_
#define NL_GAME_H_

#include <string>
#include "cereal\cereal.hpp"
#include "cereal/types/string.hpp"

namespace NLE
{
	namespace GAME
	{
		class Game
		{
		public:
			Game();
			~Game();

			template<class Archive>
			void serialize(Archive& archive)
			{
				archive(
					CEREAL_NVP(_testNum),
					CEREAL_NVP(_name),
					CEREAL_NVP(_initialScene)
					);
			}

		private:
			int _testNum;
			std::string _name;
			std::string _initialScene;
		};
	}
}

#endif