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

#include <imgui.h>

struct ImDrawData;
namespace NLE
{
	class EngineServices;
	class IWindowManager;
	class SystemServices;
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
			void drawUI(SystemServices* sServices, Size2D screenSize);
			void showEditorSettings(SystemServices* sServices, Size2D screenSize);
			void showConsole(SystemServices* sServices, Size2D screenSize);
			void showSaveGameDialog(SystemServices* sServices, Size2D screenSize);
			void showSaveSceneDialog(SystemServices* sServices, Size2D screenSize);
			void showLoadGameDialog(SystemServices* sServices, Size2D screenSize);
			void showLoadSceneDialog(SystemServices* sServices, Size2D screenSize);
			void showGameEditor(SystemServices* sServices, Size2D screenSize);
			void showSceneEditor(SystemServices* sServices, Size2D screenSize);
			void showObjectEditor(SystemServices* sServices, Size2D screenSize);
			void showScriptEditor(SystemServices* sServices, Size2D screenSize);
			void applyColorScheme(bool root);
			void restoreColorScheme();

			EngineServices& _eServices;
			CONSOLE::IConsoleQueue& _consoleQueue;
			IWindowManager& _windowManager;
			GAME::IGameManager& _gameManager;
			INPUT::IInputProcessor& _inputProcessor;
			GRAPHICS::IRenderingEngine& _renderingEngine;
			SCRIPT::IScriptingEngine& _scriptingEngine;

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

		};
	}
}

#endif