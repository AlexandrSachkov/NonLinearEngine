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


		class IGameManager : public ISystem
		{
		public:
			virtual ExecStatus getExecutionStatus() = 0;
			virtual bool hasUnsavedChanges() = 0;
			virtual void quitGame() = 0;

			virtual ~IGameManager() {}
		};
	}
}

#endif