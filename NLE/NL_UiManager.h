#ifndef NL_UI_MANAGER_H_
#define NL_UI_MANAGER_H_

#include "NL_IUiManager.h"
#include "NL_ConsoleQueue.h"

#include "tbb\concurrent_queue.h"

namespace NLE
{
	class EngineServices;
	namespace UI
	{
		class UiManager : public IUiManager
		{
		public:
			UiManager(EngineServices& eServices, CONSOLE::IConsoleQueue* consoleQueue);
			~UiManager();

			bool initialize();
			void update(SystemServices* sServices, double deltaT);

		private:			
			EngineServices& _eServices;
			CONSOLE::IConsoleQueue* _consoleQueue;
		};
	}
}

#endif
