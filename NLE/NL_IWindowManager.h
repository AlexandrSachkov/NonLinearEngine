#ifndef NL_I_WINDOW_MANAGER_H_
#define NL_I_WINDOW_MANAGER_H_

#include "NL_CommonTypes.h"

#include <string>

namespace NLE
{
	class IWindowManager
	{
	public:
		virtual bool initialize(
			Size2D screenSize,
			bool fullscreen,
			bool decorated,
			std::wstring title
			) = 0;

		virtual Size2D getClientSize() = 0;
		virtual Position2D getWindowPosition() = 0;
		virtual void* getWindowHandle() = 0;

		virtual void setTitle(std::wstring title) = 0;
		virtual void setWindowPosition(Position2D position) = 0;

		virtual void iconify() = 0;
		virtual void restore() = 0;
		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void closeWindow() = 0;
		virtual void enableCursor(bool enable) = 0;

		virtual void copyText(std::wstring text) = 0;
		virtual std::wstring pasteText() = 0;

		virtual void makeContextCurrent(bool makeCurrent) = 0;
		virtual void enableVSync(bool enable) = 0;
		virtual void swapBuffers() = 0;
		virtual void pollEvents() = 0;
	};
}

#endif