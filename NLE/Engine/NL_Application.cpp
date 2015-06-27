#include "NL_Application.h"
#include "NLCore\NL_IEngine.h"
#include "NLCore\NL_ISystem.h"
#include "NL_IApplication.h"

#include "SFML\Window.hpp"

#include <assert.h>
#include <iostream>

namespace NLE
{
	Application::Application() :
		_initialized(false)
	{
		_interface = new IApplication(*this);
	}

	Application::~Application()
	{

	}

	bool Application::initialize(Core::IEngine& engine)
	{
		assert(!_initialized);

		_window = new sf::Window(sf::VideoMode(800, 600), "NonLinear Engine");
		if (_window)
		{
			printf("Window initialized\n");
		}
		else
		{
			printf("Window failed to initialize\n");
		}
		while (_window->isOpen())
		{
			//printf("Window is open\n");
			sf::Event event;
			while (_window->pollEvent(event))
			{
				printf("Got event\n");
				if (event.type == sf::Event::Closed)
				_window->close();
			}
		}	
		
		_procedure = [&](){		
			//printf("Polling events\n");
				
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

	std::function<void()> Application::getExecutionProcedure()
	{
		return _procedure;
	}

	Core::ISystem& Application::getInterface()
	{
		return *_interface;
	}
}