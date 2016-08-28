#ifndef NL_EDITOR_UI_MANAGER_H_
#define NL_EDITOR_UI_MANAGER_H_

#include "NL_IEditorUiManager.h"
#include "NL_ConsoleQueue.h"
#include "NL_CommonTypes.h"
#include "NL_InputEvents.h"
#include "NL_Queue.h"

struct ImDrawData;
namespace NLE
{
	class EngineServices;
	class IWindowManager;
	class SystemServices;
	namespace CONSOLE
	{
		class IConsoleQueue;
	}
	namespace GAME
	{
		class IGameManager;
	}
	namespace INPUT
	{
		class IInputProcessor;
	}
	namespace GRAPHICS
	{
		class IRenderingEngine;
	}
	namespace SCRIPT
	{
		class IScriptingEngine;
	}


	namespace UI
	{
		class ImguiEditorUiManager : public IEditorUiManager
		{
		public:
			ImguiEditorUiManager(
				EngineServices& eServices,
				CONSOLE::IConsoleQueue& consoleQueue,
				IWindowManager& windowManager,
				GAME::IGameManager& gameManager,
				INPUT::IInputProcessor& inputProcessor,
				GRAPHICS::IRenderingEngine& renderingEngine,
				SCRIPT::IScriptingEngine& scriptingEngine
				);
			~ImguiEditorUiManager();

			bool initialize();

			void update(SystemServices* sServices, double deltaT, Size2D screenSize);
			void queueKeyAndCharEvent(INPUT::Event event);
			void show(bool show);
			ImDrawData* getDrawData();

		private:
			int getScancodeForKeyEvent(INPUT::Event event);
			void captureInput(SystemServices* sServices, double deltaT, Size2D screenSize);
			void drawUI(SystemServices* sServices, double deltaT, Size2D screenSize);

			EngineServices& _eServices;
			CONSOLE::IConsoleQueue& _consoleQueue;
			IWindowManager& _windowManager;
			GAME::IGameManager& _gameManager;
			INPUT::IInputProcessor& _inputProcessor;
			GRAPHICS::IRenderingEngine& _renderingEngine;
			SCRIPT::IScriptingEngine& _scriptingEngine;

			Queue<INPUT::Event> _keyAndCharEvents;
		};
	}
}

#endif
