#pragma once

#include "NL_IWindowManager.h"
#include "NL_InputEvents.h"
#include "NL_IConsoleQueue.h"

#include <string>
#include <memory>
#include <functional>

struct GLFWwindow;

namespace NLE
{
	class GlfwWindowManager : public IWindowManager
	{
	public:
		GlfwWindowManager(CONSOLE::IConsoleQueue_EServiceSP console);
		~GlfwWindowManager();

		bool initialize(
			Size2D screenSize,
			bool fullscreen,
			bool decorated,
			std::string title
			);

		Size2D getClientSize();
		Position2D getWindowPosition();
		void* getWindowHandle();
		bool getFullScreen();

		void setTitle(std::string title);
		void setWindowPosition(Position2D position);

		void iconify();
		void restore();
		void show();
		void hide();
		void closeWindow();
		void enableCursor(bool enable);

		void copyText(std::string text);
		std::string pasteText();

		void makeContextCurrent(bool makeCurrent);
		void enableVSync(bool enable);
		void swapBuffers();
		void pollEvents();

	private:
		void setDecoratedHint(bool option);
		void setResizableHint(bool option);
		void setWindowCallbacks(GLFWwindow* window);

		static void glfwErrorCallback(int error, const char* description);

		static void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void onCharEvent(GLFWwindow* window, unsigned int codepoint);
		static void onMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
		static void onCursorPositionEvent(GLFWwindow* window, double xPos, double yPos);
		static void onCursorEnterEvent(GLFWwindow* window, int entered);
		static void onScrollEvent(GLFWwindow* window, double xOffset, double yOffset);

		static void onWindowPositionEvent(GLFWwindow* window, int xPos, int yPos);
		static void onWindowSizeEvent(GLFWwindow* window, int width, int height);
		static void onWindowCloseEvent(GLFWwindow* window);
		static void onWindowRefreshEvent(GLFWwindow* window);
		static void onWindowFocusEvent(GLFWwindow* window, int focused);
		static void onWindowIconifyEvent(GLFWwindow* window, int iconified);

		static void processEvent(INPUT::Event& event);

		CONSOLE::IConsoleQueue_EServiceSP _console;
		GLFWwindow* _window;
		std::string _title;
		bool _fullScreen;
	};
}