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

#ifndef NLE_INPUT_PROCESSOR_
#define NLE_INPUT_PROCESSOR_

#include "Input\NLEInputEvents.h"

class NLE;
class NLEApplicationLayer;
class NLEInputEventListener;
class NLEInputSupply;

class NLEInputProcessor
{
public:
	static std::shared_ptr<NLEInputProcessor> instance(
		NLE* nle,
		std::shared_ptr<NLEApplicationLayer> appLayer,
		std::shared_ptr<NLEInputSupply> inputSupply
		);

	static std::shared_ptr<NLEInputProcessor> instance();
	
	~NLEInputProcessor();

	static void processInputEvent(NLE_INPUT::Event event);

	static bool registerInputEventListener(NLEInputEventListener* listener);
	static bool unregisterInputEventListener(NLEInputEventListener* listener);

private:
	NLEInputProcessor(
		NLE* nle, 
		std::shared_ptr<NLEApplicationLayer> appLayer,
		std::shared_ptr<NLEInputSupply> inputSupply
		);
	NLEInputProcessor& operator=(const NLEInputProcessor&){};
	NLEInputProcessor(const NLEInputProcessor& other);
	bool initialize();

	static std::shared_ptr<NLEInputProcessor> _inputProcessor;

	NLE* _nle;
	std::shared_ptr<NLEApplicationLayer> _appLayer;
	std::shared_ptr<NLEInputSupply> _inputSupply;

	static std::vector<NLEInputEventListener*> _inputEventListeners;
};

#endif