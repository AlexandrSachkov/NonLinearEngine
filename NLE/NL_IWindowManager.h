#ifndef NL_I_WINDOW_MANAGER_H_
#define NL_I_WINDOW_MANAGER_H_

#include "NL_CommonTypes.h"

#include <string>
#include <memory>
#include "NL_LuaCustomTypes.h"
#include "LuaIntf.h"

namespace NLE
{
	class IWindowManager
	{
	public:
		virtual bool initialize(
			Size2D screenSize,
			bool fullscreen,
			bool decorated,
			std::string title
			) = 0;

		virtual Size2D getClientSize() = 0;
		virtual Position2D getWindowPosition() = 0;
		virtual void* getWindowHandle() = 0;
		virtual bool getFullScreen() = 0;

		virtual void setTitle(std::string title) = 0;
		virtual void setWindowPosition(Position2D position) = 0;

		virtual void iconify() = 0;
		virtual void restore() = 0;
		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void closeWindow() = 0;
		virtual void enableCursor(bool enable) = 0;

		virtual void copyText(std::string text) = 0;
		virtual std::string pasteText() = 0;

		virtual void makeContextCurrent(bool makeCurrent) = 0;
		virtual void enableVSync(bool enable) = 0;
		virtual void swapBuffers() = 0;
		virtual void pollEvents() = 0;

		static void attachMasterBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
		{
			binding.beginClass<IWindowManager>("WindowManager")
				.addFunction("getClientSize", &IWindowManager::getClientSize)
				.addFunction("getWindowPosition", &IWindowManager::getWindowPosition)
				.addFunction("getFullScreen", &IWindowManager::getFullScreen)
				.addFunction("setTitle", &IWindowManager::setTitle)
				.addFunction("setWindowPosition", &IWindowManager::setWindowPosition)
				.addFunction("iconify", &IWindowManager::iconify)
				.addFunction("restore", &IWindowManager::restore)
				.addFunction("show", &IWindowManager::show)
				.addFunction("hide", &IWindowManager::hide)
				.addFunction("closeWindow", &IWindowManager::closeWindow)
				.addFunction("enableCursor", &IWindowManager::enableCursor)
				.endClass();
		}
	};

	typedef std::shared_ptr<IWindowManager> IWindowManagerSP;
}

#endif