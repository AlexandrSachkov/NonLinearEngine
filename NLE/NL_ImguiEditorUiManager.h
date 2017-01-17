#ifndef NL_EDITOR_UI_MANAGER_H_
#define NL_EDITOR_UI_MANAGER_H_

#include "NL_IEditorUiManager.h"
#include "NL_CommonTypes.h"
#include "NL_InputEvents.h"
#include "NL_Queue.h"
#include "NL_CircularBuffer.h"
#include "NL_IConsoleQueue.h"
#include "NL_CharBuffer.h"
#include "NL_ImguiGameEditor.h"
#include "NL_ImguiSceneEditor.h"
#include "NL_ImguiObjectEditor.h"
#include "NL_ImguiScriptEditor.h"
#include "NL_EngineServices.h"
#include "NL_IWindowManager.h"
#include "NL_IInputProcessor.h"
#include "NL_IRenderingEngine.h"
#include "NL_IScriptingEngine.h"
#include "NL_IGameManager.h"
#include "NL_ScriptExecutor.h"

#include <imgui.h>

struct ImDrawData;
namespace NLE
{
	class SystemServices;

	namespace UI
	{
		class ImguiEditorUiManager : public IEditorUiManager
		{
		public:
			ImguiEditorUiManager(
				EngineServices eServices,
				CONSOLE::IConsoleQueueSP consoleQueue,
				IWindowManagerSP windowManager,
				GAME::IGameManagerSP gameManager,
				INPUT::IInputProcessorSP inputProcessor,
				GRAPHICS::IRenderingEngineSP renderingEngine,
				SCRIPT::IScriptingEngineSP scriptingEngine,
				SCRIPT::ScriptExecutor& masterExecutor
				);
			~ImguiEditorUiManager();

			bool initialize();

			void update(SystemServices& sServices, double deltaT, Size2D screenSize);
			void queueKeyAndCharEvent(INPUT::Event event);
			void show(bool show);
			ImDrawData* getDrawData();

		private:
			int getScancodeForKeyEvent(INPUT::Event event);
			void captureInput(double deltaT, Size2D screenSize);
			void drawUI(Size2D screenSize);
			void showEditorSettings(Size2D screenSize);
			void showConsole(Size2D screenSize);
			void showSaveGameDialog(Size2D screenSize);
			void showSaveSceneDialog(Size2D screenSize);
			void showLoadGameDialog(Size2D screenSize);
			void showLoadSceneDialog(Size2D screenSize);
			void showGameEditor(Size2D screenSize);
			void showSceneEditor(Size2D screenSize);
			void showObjectEditor(Size2D screenSize);
			void showScriptEditor(Size2D screenSize);
			void applyColorScheme(bool root);
			void restoreColorScheme();
			void showCommandPrompt();

			EngineServices _eServices;
			CONSOLE::IConsoleQueueSP _consoleQueue;
			IWindowManagerSP _windowManager;
			GAME::IGameManagerSP _gameManager;
			INPUT::IInputProcessorSP _inputProcessor;
			GRAPHICS::IRenderingEngineSP _renderingEngine;
			SCRIPT::IScriptingEngineSP _scriptingEngine;

			Queue<INPUT::Event> _keyAndCharEvents;

			bool _showEditor;
			bool _showEditorSettings;
			bool _showConsole;
			bool _showSaveGameDialog;
			bool _showSaveSceneDialog;
			bool _showLoadGameDialog;
			bool _showLoadSceneDialog;
			CharBuffer _saveGameBuff;
			CharBuffer _saveSceneBuff;
			CharBuffer _loadGameBuff;
			CharBuffer _loadSceneBuff;

			ImguiGameEditor _gameEditor;
			ImguiSceneEditor _sceneEditor;
			ImguiObjectEditor _objectEditor;
			ImguiScriptEditor _scriptEditor;
			CircularBuffer<std::pair<CONSOLE::OUTPUT_TYPE, std::string>> _consoleLogs;

			ImVec4 _windowBgColor;
			ImVec4 _textColor;
			ImVec4 _borderColor;
			ImVec4 _itemColor;
			ImVec4 _itemHoverColor;
			ImVec4 _itemActiveColor;
			ImVec4 _selectionColor;

			CharBuffer _commandBuffer;
			SCRIPT::ScriptExecutor& _masterExecutor;
		};
	}
}

#endif
