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
#include "Input\NLEInputProcessor.h"
#include "Input\NLEInputEventListener.h"
#include "Input\NLEInputSupply.h"
#include "Application\NLEApplicationLayer.h"


std::vector<NLEInputEventListener*> NLEInputProcessor::_inputEventListeners;
std::shared_ptr<NLEInputProcessor> NLEInputProcessor::_inputProcessor = NULL;

std::shared_ptr<NLEInputProcessor> NLEInputProcessor::instance(
	std::shared_ptr<NLEApplicationLayer> appLayer,
	std::shared_ptr<NLEInputSupply> inputSupply
	)
{
	if (!_inputProcessor)
	{
		_inputProcessor.reset(new NLEInputProcessor(appLayer, inputSupply));
	}
	return _inputProcessor;
}

std::shared_ptr<NLEInputProcessor> NLEInputProcessor::instance()
{
	if (!_inputProcessor)
	{
		throw std::runtime_error("GUI Manager is not initialized, use instance(NLE* nle)");
	}
	else
	{
		return _inputProcessor;
	}
}

NLEInputProcessor::NLEInputProcessor(
	std::shared_ptr<NLEApplicationLayer> appLayer,
	std::shared_ptr<NLEInputSupply> inputSupply
	)
{
	_appLayer = appLayer;
	_inputSupply = inputSupply;

	if (!initialize())
	{
		NLE_Log::err(NLE_Log::CRITICAL, "NLE Input Processor failed to initialize.");
		throw std::exception("NLE Input Processor failed to initialize.");
	}
	NLE_Log::console("======> NLEInputProcessor successfully initialized.");
}


bool NLEInputProcessor::initialize()
{
	_running = false;
	_inputSupply->bindInputEventCallback(&NLEInputProcessor::processInputEvent);

	return true;
}

NLEInputProcessor::~NLEInputProcessor()
{

}

void NLEInputProcessor::run()
{
	_running = true;
}

void NLEInputProcessor::stop()
{
	_running = false;
}

bool NLEInputProcessor::isRunning()
{
	return _running;
}

bool NLEInputProcessor::registerInputEventListener(NLEInputEventListener* listener)
{
	if (listener)
	{
		_inputEventListeners.push_back(listener);
		return true;
	}
	return false;
}

bool NLEInputProcessor::unregisterInputEventListener(NLEInputEventListener* listener)
{
	if (listener)
	{
		for (unsigned i = 0; i < _inputEventListeners.size(); i++)
		{
			if (_inputEventListeners.at(i) == listener)
			{
				_inputEventListeners.erase(_inputEventListeners.begin() + i);
				return true;
			}
		}
	}
	return false;
}

void NLEInputProcessor::processInputEvent(NLE_INPUT::Event event)
{
	if (_inputProcessor->isRunning())
	{
		for (unsigned i = 0; i < _inputEventListeners.size(); i++)
		{
			_inputEventListeners.at(i)->processInputEvent(event);
		}
	}
}