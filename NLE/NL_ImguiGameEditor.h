#ifndef NL_IMGUI_GAME_EDITOR_H_
#define NL_IMGUI_GAME_EDITOR_H_

#include "NL_CommonTypes.h"
#include "NL_CharBuffer.h"
#include "NL_IConsoleQueue.h"

namespace NLE
{
	namespace GAME
	{
		class IGameManager;
	}
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
				CONSOLE::IConsoleQueue& consoleQueue, 
				GAME::IGameManager& gameManager, 
				Size2D screenSize,
				ImguiScriptEditor& scriptEditor
				);
		private:
			ImguiGameEditor& operator=(ImguiGameEditor& other) = delete;

			bool _visible;
			CharBuffer _nameBuff;
			int _selectedScript;
		};
	}
}

#endif