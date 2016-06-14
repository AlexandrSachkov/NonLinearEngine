#ifndef NL_UI_MANAGER_H_
#define NL_UI_MANAGER_H_

#include "NL_IUiManager.h"
#include "NL_ISystem.h"
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
		class UiManager : public IUiManager, public ISystem
		{
		public:
			UiManager(EngineServices& eServices, CONSOLE::ConsoleQueue& consoleQueue);
			~UiManager();

			bool initialize();
			void update(SystemServices& sServices, DataManager& data, double deltaT);

		private:			
			EngineServices& _eServices;
			CONSOLE::ConsoleQueue& _consoleQueue;
		};
	}
}

#endif
