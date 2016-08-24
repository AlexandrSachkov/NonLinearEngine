#ifndef NL_EDITOR_UI_MANAGER_H_
#define NL_EDITOR_UI_MANAGER_H_

#include "NL_IEditorUiManager.h"
#include "NL_ConsoleQueue.h"

#include "tbb\concurrent_queue.h"

namespace NLE
{
	class EngineServices;
	namespace UI
	{
		class EditorUiManager : public IEditorUiManager
		{
		public:
			EditorUiManager(EngineServices& eServices, CONSOLE::IConsoleQueue* consoleQueue);
			~EditorUiManager();

			bool initialize();
			void update(SystemServices* sServices, double deltaT);

		private:			
			EngineServices& _eServices;
			CONSOLE::IConsoleQueue* _consoleQueue;
		};
	}
}

#endif
