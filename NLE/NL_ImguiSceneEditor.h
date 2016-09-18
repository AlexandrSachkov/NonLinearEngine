#ifndef NL_IMGUI_SCENE_EDITOR_H_
#define NL_IMGUI_SCENE_EDITOR_H_

#include "NL_CommonTypes.h"
#include "NL_CharBuffer.h"

namespace NLE
{
	namespace GAME
	{
		class IGameManager;
	}
	namespace UI
	{
		class ImguiSceneEditor
		{
		public:
			ImguiSceneEditor();
			~ImguiSceneEditor();

			bool& getVisibility();
			void draw(GAME::IGameManager& gameManager, Size2D screenSize);
		private:
			ImguiSceneEditor& operator=(ImguiSceneEditor& other) = delete;

			bool _visible;
			CharBuffer _nameBuff;
		};
	}
}

#endif