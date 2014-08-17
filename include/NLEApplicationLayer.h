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

#ifndef NLE_APPLICATION_LAYER_
#define NLE_APPLICATION_LAYER_

#include "NLESingleInstance.h"

class NLE;
class GLFWwindow;

class NLEApplicationLayer : private NLESingleInstance<NLEApplicationLayer>
{
	friend class NLEInputProcessor;
public:

	NLEApplicationLayer(NLE* nle);
	~NLEApplicationLayer();

	NLEWindowReference& getWindowReference();
	void getClientSize(int& width, int& height);
	void setClientSize(int width, int height);
	void setResizableHint(bool option);
	void setDecoratedHint(bool option);
	void setTitle(std::wstring title);
	void setPosition(int x, int y);
	void getPosition(int& x, int& y);
	void iconify();
	void restore();
	void show();
	void hide();

	int runMessageLoop();
	void endMessageLoop();

	void copyClipboard(std::wstring text);
	void cutClipboard(std::wstring text);
	std::wstring pasteClipboard();

private:	
	NLEApplicationLayer(const NLEApplicationLayer& other);
	bool initialize();

	static void debugCallback(char text[]);
	static void consoleCallback(char text[]);
	static void errorCallback(NLE_Log::ErrorFlag flag, char text[]);
	static void glfwErrorCallback(int error, const char* description);

	GLFWwindow* getGLFWwindow();
	NLE* _nle;
	GLFWwindow* _window;
};

#endif