#ifndef NL_IMGUI_SCENE_VIEWER_H_
#define NL_IMGUI_SCENE_VIEWER_H_

#include "NL_CharBuffer.h"
#include "NL_IGameManager.h"

namespace NLE
{
	namespace GAME
	{
		class IGameManager;
	}
	namespace UI
	{
		class ImguiSceneViewer
		{
		public:
			ImguiSceneViewer();
			~ImguiSceneViewer();

			void draw(const GAME::IGameManagerSP& gameManager);
		private:
			CharBuffer _sceneNameBuff;
			CharBuffer _scenePathBuff;
			bool _showAddSceneDialog;
			int _selectedScene;
		};
	}
}

#endif