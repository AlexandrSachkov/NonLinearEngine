#ifndef NL_IMGUI_OBJECT_EDITOR_H_
#define NL_IMGUI_OBJECT_EDITOR_H_

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
		class ImguiObjectEditor
		{
		public:
			ImguiObjectEditor();
			~ImguiObjectEditor();

			bool& getVisibility();
			void draw(GAME::IGameManager& gameManager, Size2D screenSize);
		private:
			ImguiObjectEditor& operator=(ImguiObjectEditor& other) = delete;

			bool _visible;
			CharBuffer _nameBuff;
		};
	}
}

#endif