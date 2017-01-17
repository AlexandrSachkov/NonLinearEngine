#pragma once

#include "NL_CommonTypes.h"
#include "NL_CharBuffer.h"
#include "NL_IConsoleQueue.h"
#include "NL_ImguiScriptViewer.h"
#include "NL_IGameManager.h"

namespace NLE
{
	namespace UI
	{
		class ImguiSceneEditor
		{
		public:
			ImguiSceneEditor();
			~ImguiSceneEditor();

			bool& getVisibility();
			void draw(
				const CONSOLE::IConsoleQueueSP& consoleQueue, 
				const GAME::IGameManagerSP& gameManager, 
				Size2D screenSize,
				ImguiScriptEditor& scriptEditor
				);
		private:
			ImguiSceneEditor& operator=(ImguiSceneEditor& other) = delete;

			bool _visible;
			CharBuffer _nameBuff;
			ImguiScriptViewer _scriptViewer;
		};
	}
}