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
#include "stdafx.h"
#include "InputProcessor\NLEInputProcessor.h"
#include "InputProcessor\NLEInputListener.h"
#include "NLEApplicationLayer.h"
#include "NLE.h"
#include "GLFW\glfw3.h"

std::vector<NLEInputListener*> NLEInputProcessor::_inputListeners;

NLEInputProcessor::NLEInputProcessor(
	NLE* nle, 
	std::shared_ptr<NLEApplicationLayer> appLayer
	)
{
	_nle = nle;
	_appLayer = appLayer;
	_window = NULL;

	if (!initialize())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "NLE Input Processor failed to initialize.");
		throw std::exception("NLE Input Processor failed to initialize.");
	}
	NLE_Log::console("======> NLEInputProcessor successfully initialized.");
}


bool NLEInputProcessor::initialize()
{
	_window = _appLayer->getGLFWwindow();

	glfwSetKeyCallback(_window,onKeyEvent);
	glfwSetCharCallback(_window, onCharEvent);
	glfwSetMouseButtonCallback(_window, onMouseButtonEvent);
	glfwSetCursorPosCallback(_window, onCursorPositionEvent);
	glfwSetCursorEnterCallback(_window, onCursorEnterEvent);
	glfwSetScrollCallback(_window, onScrollEvent);

	glfwSetWindowPosCallback(_window, onWindowPositionEvent);
	glfwSetWindowSizeCallback(_window, onWindowSizeEvent);
	glfwSetWindowCloseCallback(_window, onWindowCloseEvent);
	glfwSetWindowRefreshCallback(_window, onWindowRefreshEvent);
	glfwSetWindowFocusCallback(_window, onWindowFocusEvent);
	glfwSetWindowIconifyCallback(_window, onWindowIconifyEvent);


	return true;
}

NLEInputProcessor::~NLEInputProcessor()
{

}

bool NLEInputProcessor::registerInputListener(NLEInputListener* listener)
{
	if (listener)
	{
		_inputListeners.push_back(listener);
		return true;
	}
	return false;
}

bool NLEInputProcessor::unregisterInputListener(NLEInputListener* listener)
{
	if (listener)
	{
		for (unsigned i = 0; i < _inputListeners.size(); i++)
		{
			if (_inputListeners.at(i) == listener)
			{
				_inputListeners.erase(_inputListeners.begin() + i);
				return true;
			}
		}
	}
	return false;
}

void NLEInputProcessor::onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	for (unsigned int i = 0; i < _inputListeners.size(); i++)
	{
		_inputListeners.at(i)->onKeyEvent(
			static_cast<NLE_INPUT::KEY>(key),
			scancode,
			static_cast<NLE_INPUT::ACTION>(action),
			static_cast<NLE_INPUT::MOD>(mods)
			);
	}
}

void NLEInputProcessor::onCharEvent(GLFWwindow *window, unsigned int codepoint)
{
	for (unsigned int i = 0; i < _inputListeners.size(); i++)
	{
		_inputListeners.at(i)->onCharEvent(codepoint);
	}
}

void NLEInputProcessor::onMouseButtonEvent(GLFWwindow *window, int button, int action, int mods)
{
	for (unsigned int i = 0; i < _inputListeners.size(); i++)
	{
		_inputListeners.at(i)->onMouseButtonEvent(
			static_cast<NLE_INPUT::MOUSE>(button),
			static_cast<NLE_INPUT::ACTION>(action),
			static_cast<NLE_INPUT::MOD>(mods)
			);
	}
}

void NLEInputProcessor::onCursorPositionEvent(GLFWwindow *window, double xPos, double yPos)
{
	for (unsigned int i = 0; i < _inputListeners.size(); i++)
	{
		_inputListeners.at(i)->onCursorPositionEvent(xPos, yPos);
	}
}

void NLEInputProcessor::onCursorEnterEvent(GLFWwindow *window, int entered)
{
	for (unsigned int i = 0; i < _inputListeners.size(); i++)
	{
		_inputListeners.at(i)->onCursorEnterEvent(entered == GL_TRUE ? true : false);
	}
}

void NLEInputProcessor::onScrollEvent(GLFWwindow *window, double xOffset, double yOffset)
{
	for (unsigned int i = 0; i < _inputListeners.size(); i++)
	{
		_inputListeners.at(i)->onScrollEvent(xOffset, yOffset);
	}
}

void NLEInputProcessor::onWindowPositionEvent(GLFWwindow *window, int xPos, int yPos)
{

}

void NLEInputProcessor::onWindowSizeEvent(GLFWwindow *window, int width, int height)
{

}

void NLEInputProcessor::onWindowCloseEvent(GLFWwindow *window)
{

}

void NLEInputProcessor::onWindowRefreshEvent(GLFWwindow *window)
{

}

void NLEInputProcessor::onWindowFocusEvent(GLFWwindow *window, int focused)
{

}

void NLEInputProcessor::onWindowIconifyEvent(GLFWwindow *window, int iconified)
{

}

void NLEInputProcessor::onClipboardCopy()
{

}

void NLEInputProcessor::onClipboardCut()
{

}

void NLEInputProcessor::onClipboardPaste()
{

}


