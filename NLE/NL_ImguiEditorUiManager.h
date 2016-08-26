#ifndef NL_EDITOR_UI_MANAGER_H_
#define NL_EDITOR_UI_MANAGER_H_

#include "NL_IEditorUiManager.h"
#include "NL_ConsoleQueue.h"
#include "NL_CommonTypes.h"

#include "tbb\concurrent_queue.h"

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

			bool initialize(Size2D screenSize);

			void update(SystemServices* sServices, double deltaT, Size2D screenSize);
			void show(bool show);
			ImDrawData* getDrawData();

		private:
			EngineServices& _eServices;
			CONSOLE::IConsoleQueue& _consoleQueue;
			IWindowManager& _windowManager;
			GAME::IGameManager& _gameManager;
			INPUT::IInputProcessor& _inputProcessor;
			GRAPHICS::IRenderingEngine& _renderingEngine;
			SCRIPT::IScriptingEngine& _scriptingEngine;
		};
	}
}

#endif
