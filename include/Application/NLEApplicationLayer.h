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

class NLEApplicationLayer
{
public:
	~NLEApplicationLayer(){};

	virtual NLEWindowReference& getWindowReference() =0;
	virtual void getClientSize(int& width, int& height) = 0;
	virtual void setClientSize(int width, int height) = 0;
	virtual void setResizable(bool option) = 0;
	virtual void setDecorated(bool option) = 0;
	virtual void setTitle(std::wstring title) = 0;
	virtual void setWindowPosition(int x, int y) = 0;
	virtual void getWindowPosition(int& x, int& y) = 0;
	virtual void iconify() = 0;
	virtual void restore() = 0;
	virtual void show() = 0;
	virtual void hide() = 0;

	virtual int runMessageLoop() = 0;
	virtual void endMessageLoop() = 0;

	virtual void copyText(std::wstring text) = 0;
	virtual std::wstring pasteText() = 0;
};

#endif