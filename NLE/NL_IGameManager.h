#ifndef NL_IGAME_MANAGER_H_
#define NL_IGAME_MANAGER_H_

#include <string>

namespace NLE
{
	namespace GAME
	{
		enum CommandType
		{
			QUIT_GAME,
			RESTART_GAME
		};

		union CommandData
		{
		};

		struct Command
		{
			Command() {}
			Command(CommandType type) : type(type) {}
			Command(CommandType type, CommandData data) : type(type), data(data) {}
			CommandType type;
			CommandData data;
		};

		class IGameManager
		{
		public:
			virtual void queueCommand(Command& command) = 0;
		};
	}
}

#endif