#ifndef NL_UI_MANAGER_H_
#define NL_UI_MANAGER_H_

#include "NL_IUiManager.h"
#include "NL_EngineServices.h"
#include "NL_ConsoleQueue.h"

#include "tbb\concurrent_queue.h"

namespace NLE
{
	namespace Core
	{
		class IEngine;
		class ISystem;
		struct SysInitializer;
	}

	namespace UI
	{
		class UiManager : public IUiManager
		{
		public:
			UiManager(EngineServices& eServices, CONSOLE::IConsoleQueue* consoleQueue);
			~UiManager();

			bool initialize();
			void update(SystemServices* sServices, DataManager* data, double deltaT);

		private:			
			EngineServices& _eServices;
			CONSOLE::IConsoleQueue* _consoleQueue;
		};
	}
}

#endif
