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



#ifndef NLE_GUI_MANAGER_
#define NLE_GUI_MANAGER_

#include "GUI\NLEGuiManagerInterface.h"
#include "Input\NLEInputEventListener.h"
#include <memory>
#include <cstdio>

class NLRE;
namespace CEGUI
{
	class Direct3D11Renderer;
	class GUIContext;
	class String;
	class Window;
};

class NLEGuiManager : public NLEGuiManagerInterface, public NLEInputEventListener
{
public:
	static std::shared_ptr<NLEGuiManager> instance(
		std::shared_ptr<NLRE> renderingEngine
		);
	static std::shared_ptr<NLEGuiManager> instance();
	~NLEGuiManager();

	void updateUI();
	void showFPS(bool option);
	void setDataFilesRootPath(std::wstring path);

	void processInputEvent(NLE_INPUT::Event event);
	static void renderGUI();

private:
	NLEGuiManager(
		std::shared_ptr<NLRE> renderingEngine
		);
	NLEGuiManager(const NLEGuiManager&);
	NLEGuiManager& operator=(const NLEGuiManager&){};
	bool initialize();

	static std::shared_ptr<NLEGuiManager> _guiManager;
	std::shared_ptr<NLRE> _renderingEngine;

	CEGUI::Direct3D11Renderer* _guiRenderer;
	CEGUI::GUIContext* _guiContext;

	CEGUI::Window* _rootWindow;
	CEGUI::Window* _fpsCountLabel;
};

#endif