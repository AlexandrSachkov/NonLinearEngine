/*
-----------------------------------------------------------------------------
This source file is part of NLE
(NonLinear Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearEngine

Copyright (c) 2014 Alexandr Sachkov & NonLinear Engine Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef NLE_GLFW_APPLICATION_LAYER_
#define NLE_GLFW_APPLICATION_LAYER_

#include "NLE\Engine\NL_InputEvents.h"
#include "NLE\Engine\NL_INle.h"
#include <string>
#include <memory>

struct GLFWwindow;
class NLEInterface;

class NLEGlfwApplicationLayer
{
public:
	static NLEGlfwApplicationLayer& instance();
	~NLEGlfwApplicationLayer();	
	bool initialize();

	void getClientSize(int& width, int& height);
	void getWindowPosition(int& x, int& y);

	void setWindowSizeHint(int width, int height);
	void setFullscreenHint(bool option);
	void setDecoratedHint(bool option);
	void setTitle(std::wstring title);
	void setWindowPosition(int x, int y);
	
	void iconify();
	void restore();
	void show();
	void hide();
	int runMessageLoop();
	void closeWindow();

	void copyText(std::wstring text);
	std::wstring pasteText();

	bool bindInputEventCallback(void(*processEvent)(NLE_INPUT::Event event));
	NLE::INle* getNLE();

private:	
	NLEGlfwApplicationLayer();
	NLEGlfwApplicationLayer(const NLEGlfwApplicationLayer& other) = delete;
	NLEGlfwApplicationLayer& operator=(const NLEGlfwApplicationLayer&) = delete;

	void setWindowCallbacks(GLFWwindow* window);
	void setResizableHint(bool option);

	static void glfwErrorCallback(int error, const char* description);

	static void onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void onCharEvent(GLFWwindow *window, unsigned int codepoint);
	static void onMouseButtonEvent(GLFWwindow *window, int button, int action, int mods);
	static void onCursorPositionEvent(GLFWwindow *window, double xPos, double yPos);
	static void onCursorEnterEvent(GLFWwindow *window, int entered);
	static void onScrollEvent(GLFWwindow *window, double xOffset, double yOffset);

	static void onWindowPositionEvent(GLFWwindow *window, int xPos, int yPos);
	static void onWindowSizeEvent(GLFWwindow *window, int width, int height);
	static void onWindowCloseEvent(GLFWwindow *window);
	static void onWindowRefreshEvent(GLFWwindow *window);
	static void onWindowFocusEvent(GLFWwindow *window, int focused);
	static void onWindowIconifyEvent(GLFWwindow *window, int iconified);

	static void onClipboardCopyEvent();
	static void onClipboardCutEvent();
	static void onClipboardPasteEvent();

	static NLEGlfwApplicationLayer* _glfwAppLayer;

	NLE::INle* _nle;
	std::string _title;
	int _width;
	int _height;
	bool _fullscreen;

	GLFWwindow* _window;
};

#endif