#ifndef NL_IMGUI_GAME_EDITOR_H_
#define NL_IMGUI_GAME_EDITOR_H_

#include "NL_CommonTypes.h"
#include "NL_CharBuffer.h"
#include "NL_IConsoleQueue.h"
#include "NL_ImguiScriptViewer.h"
#include "NL_ImguiSceneViewer.h"
#include "NL_IGameManager.h"

namespace NLE
{
	namespace UI
	{
		class ImguiScriptEditor;
		class ImguiGameEditor
		{
		public:
			ImguiGameEditor();
			~ImguiGameEditor();

			bool& getVisibility();
			void draw(
				const CONSOLE::IConsoleQueueSP& consoleQueue, 
				const GAME::IGameManagerSP& gameManager, 
				Size2D screenSize,
				ImguiScriptEditor& scriptEditor
				);
		private:
			ImguiGameEditor& operator=(ImguiGameEditor& other) = delete;

			bool _visible;
			CharBuffer _nameBuff;
			int _selectedScript;
			ImguiScriptViewer _scriptViewer;
			ImguiSceneViewer _sceneViewer;
		};
	}
}

#endif