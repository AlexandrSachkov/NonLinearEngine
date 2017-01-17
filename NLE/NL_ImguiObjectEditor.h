#pragma once

#include "NL_CommonTypes.h"
#include "NL_CharBuffer.h"
#include "NL_IGameManager.h"

namespace NLE
{
	namespace UI
	{
		class ImguiObjectEditor
		{
		public:
			ImguiObjectEditor();
			~ImguiObjectEditor();

			bool& getVisibility();
			void draw(const GAME::IGameManagerSP& gameManager, Size2D screenSize);
		private:
			ImguiObjectEditor& operator=(ImguiObjectEditor& other) = delete;

			bool _visible;
			CharBuffer _nameBuff;
		};
	}
}