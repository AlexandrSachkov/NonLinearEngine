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
#include "NLELog.h"
#include "NLE.h"
#include "RenderingEngine\NLRE.h"
#include "RenderingEngine\SceneManager\NLRESceneManager.h"
#include "Input\NLEInputProcessor.h"
#include "GUI\NLEGuiManager.h"


NLE* NLE::_nle = nullptr;

//===========================================================================================================================
NLEInterface* NLE::instance(
	NLEWindowReference winRef,
	int width,
	int height,
	bool fullScreen
	)
{
	if (!_nle)
	{
		_nle = new NLE(winRef, width, height, fullScreen);
	}
	return _nle;
}

//===========================================================================================================================
NLE::NLE(
	NLEWindowReference winRef,
	int width,
	int height,
	bool fullScreen
	)
{
	_initialized = false;

	_winRef = winRef;
	_width = width;
	_height = height;
	_fullScreen = fullScreen;

	setupLogCallbacks();
	_log = NLE_Log::instance();

	NLE_Log::console("======> NLE successfully created.");
}

//===========================================================================================================================
NLE::~NLE()
{
	stop();
	_initialized = false;
}

//===========================================================================================================================
bool NLE::initialize()
{
	try
	{
		_renderingEngine = NLRE::instance(_winRef, _width, _height, _fullScreen);
		_guiManager = NLEGuiManager::instance(_renderingEngine, _guiDataFilesRootPath);
		_inputProcessor = NLEInputProcessor::instance();
	}
	catch (std::exception& e)
	{
		NLE_Log::err(NLE_Log::CRITICAL, "NonLinear Engine failed to initialize: %s", e.what());
		return false;
	}

	_initialized = true;
	NLE_Log::console("======> NLE successfully initialized.");
	return true;
}

//===========================================================================================================================
void NLE::release()
{
	delete this;
}

//===========================================================================================================================
bool NLE::isInitialized()
{
	return _initialized;
}

//===========================================================================================================================
void NLE::setupLogCallbacks()
{
	NLRE_Log::registerDebugCallback(NLE::NLREdebugOutputHook);
	NLRE_Log::registerConsoleCallback(NLE::NLREconsoleOutputHook);
	NLRE_Log::registerErrorCallback(NLE::NLREerrorOutputHook);
}

//===========================================================================================================================
void NLE::NLREdebugOutputHook(char text[])
{
	NLE_Log::debug(text);
}

//===========================================================================================================================
void NLE::NLREconsoleOutputHook(char text[])
{
	NLE_Log::console(text);
}

//===========================================================================================================================
void NLE::NLREerrorOutputHook(NLRE_Log::ErrorFlag flag, char text[])
{
	NLE_Log::err((NLE_Log::ErrorFlag)flag, text);
}

//===========================================================================================================================
void NLE::run()
{
	if (isInitialized())
	{
		_inputProcessor->run();
		_renderingEngine->run();
		_running = true;
	}
}

//===========================================================================================================================
void NLE::stop()
{
	if (isInitialized())
	{
		_inputProcessor->stop();
		_renderingEngine->stop();
		_running = false;
	}
}

//===========================================================================================================================
void NLE::onTick()
{
	if (isRunning())
	{
		_guiManager->updateUI();
		_renderingEngine->render();
	}
}

//===========================================================================================================================
void NLE::setGUIDataFilesRootPath(std::wstring path)
{
	fs::path guiDataRootPath(path);
	guiDataRootPath.make_preferred();

	if (guiDataRootPath.has_relative_path() || guiDataRootPath.is_absolute())
	{
		_guiDataFilesRootPath = guiDataRootPath.generic_wstring();
	}
}

//===========================================================================================================================
bool NLE::isRunning()
{
	return _running;
}

//===========================================================================================================================
std::shared_ptr<NLELogInterface> NLE::getLog()
{
	return std::dynamic_pointer_cast<NLELogInterface>(_log);
}

//===========================================================================================================================
std::shared_ptr<NLREInterface> NLE::getRenderingEngine()
{
	return std::dynamic_pointer_cast<NLREInterface>(_renderingEngine);
}

//===========================================================================================================================
std::shared_ptr<NLEInputProcessorInterface> NLE::getInputProcessor()
{
	return std::dynamic_pointer_cast<NLEInputProcessorInterface>(_inputProcessor);
}

//===========================================================================================================================
std::shared_ptr<NLEGuiManagerInterface> NLE::getGuiManager()
{
	return std::dynamic_pointer_cast<NLEGuiManagerInterface>(_guiManager);
}

