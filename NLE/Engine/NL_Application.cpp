#include "NL_Application.h"
#include "NLCore\NL_IEngine.h"
#include "NLCore\NL_ISystem.h"

#include <assert.h>
#include <iostream>

namespace NLE
{
	Application::Application() :
		_initialized(false)
	{

	}

	Application::~Application()
	{

	}

	bool Application::initialize(Core::IEngine& engine)
	{
		assert(!_initialized);
	
		_procedure = [&](){		
			
				
		};

		_initialized = true;
		return true;
	}

	void Application::release()
	{
		_initialized = false;
	}

	bool Application::initialized()
	{
		return _initialized;
	}

	std::function<void()> const& Application::getExecutionProcedure()
	{
		return _procedure;
	}

	Core::ISystem& Application::getInterface()
	{
		return *this;
	}
}