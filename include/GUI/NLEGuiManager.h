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

#include "InputProcessor\NLEInputListener.h"
#include "InputProcessor\NLEInputMap.h"
#include "CEGUI\Clipboard.h"

class NLE;
class NLEApplicationLayer;
namespace CEGUI
{
	class Direct3D11Renderer;
	class String;
};

class NLEGuiManager : public NLEInputListener, public CEGUI::NativeClipboardProvider
{
public:
	static std::shared_ptr<NLEGuiManager> instance(
		NLE* nle, 
		std::shared_ptr<NLEApplicationLayer> appLayer
		);
	static std::shared_ptr<NLEGuiManager> instance();
	~NLEGuiManager();

	void sendToClipboard(const CEGUI::String &mimeType, void *buffer, size_t size);
	void retrieveFromClipboard(CEGUI::String &mimeType, void *&buffer, size_t &size);

	static void renderGUI();

private:
	NLEGuiManager(NLE* nle, std::shared_ptr<NLEApplicationLayer> appLayer);
	NLEGuiManager(const NLEGuiManager&);
	NLEGuiManager& operator=(const NLEGuiManager&){};
	bool initialize();

	void onKeyEvent(NLE_INPUT::KEY key, int scancode, NLE_INPUT::ACTION action, NLE_INPUT::MOD mods);
	void onCharEvent(unsigned int codepoint);
	void onMouseButtonEvent(NLE_INPUT::MOUSE button, NLE_INPUT::ACTION action, NLE_INPUT::MOD mods);
	void onCursorPositionEvent(double xPos, double yPos);
	void onCursorEnterEvent(bool entered);
	void onScrollEvent(double xOffset, double yOffset);

	static std::shared_ptr<NLEGuiManager> _guiManager;
	NLE* _nle;
	std::shared_ptr<NLEApplicationLayer> _appLayer;
	CEGUI::Direct3D11Renderer* _guiRenderer;
};

#endif