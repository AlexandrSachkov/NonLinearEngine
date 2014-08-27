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


#ifndef NLE_
#define NLE_

#include "RenderingEngine\NLREMain\NLRELog.h"
#include "NLEWindowReference.h"
#include "NLEInterface.h"
#include "NLESingleInstance.h"
#include "NLEDllApi.h"

class NLE_Log;
class NLELogInterface;
class NLEInputProcessor;
class NLRE;
class NLEGuiManager;

class NLE : public NLEInterface, public NLESingleInstance<NLE>
{
public:	
	NLE(
		NLEWindowReference winRef,
		int width,
		int height
		);
	~NLE();
	bool initialize();
	void release();

	void run();
	void stop();
	void onTick();
	bool isRunning();

	std::shared_ptr<NLELogInterface> getLog();
	std::shared_ptr<NLRE> getRenderingEngine();
	std::shared_ptr<NLEInputProcessor> getInputProcessor();
	std::shared_ptr<NLEGuiManager> getGuiManager();

private:

	NLE(const NLE& other){}
	NLEInputProcessor& operator=(const NLEInputProcessor&){}

	bool initializeWindow();
	void setupLogCallbacks();

	static void NLREdebugOutputHook(char text[]);
	static void NLREconsoleOutputHook(char text[]);
	static void NLREerrorOutputHook(NLRE_Log::ErrorFlag flag, char text[]);

	NLEWindowReference _winRef;
	int _width;
	int _height;

	bool _running;
	bool _initialized;

	std::shared_ptr<NLE_Log> _log;
	std::shared_ptr<NLEInputProcessor> _inputProcessor;
	std::shared_ptr<NLRE> _renderingEngine;
	std::shared_ptr<NLEGuiManager> _guiManager;
};

#if defined (_NLE_DLL_) && defined(_NLE_DLL_EXPORT_)
extern "C" _NLE_API_ NLEInterface* APIENTRY GetNLE(
	NLEWindowReference winRef,
	int width,
	int height
	)
{
	return new NLE(winRef, width, height);
}
#elif defined(_NLE_DLL_)
extern "C" _NLE_API_ NLEInterface* GetNLE(
	NLEWindowReference winRef,
	int width,
	int height
	);
#endif
#endif