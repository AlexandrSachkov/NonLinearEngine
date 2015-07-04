#include "NL_Renderer.h"
#include "NLCore\NL_ISystem.h"
#include "NLCore\NL_IEngine.h"

#include <assert.h>

namespace NLE
{
	namespace GRAPHICS
	{
		Renderer::Renderer() :
			_initialized(false)
		{
			_running.fetch_and_store(false);
		}

		Renderer::~Renderer()
		{

		}

		bool Renderer::initialize(Core::IEngine& engine)
		{
			assert(!_initialized && _makeContextCurrent && _swapBuffers);

			_procedure = [&](){
				printf("Starting Rendering task\n");

				_running.fetch_and_store(true);
				_renderingThread = new std::thread([&](GRAPHICS::Renderer* renderer){

					printf("Rendering Thread running");			
					renderer->makeContextCurrent();
					while (renderer->isRunning())
					{
						
						renderer->swapBuffers();
					}
				}, this);
				_renderingThread->detach();
			};

			_initialized = true;
			return true;
		}

		bool Renderer::isRunning()
		{
			return _running;
		}
		
		void Renderer::stop()
		{
			_running.fetch_and_store(false);
		}
		
		void Renderer::makeContextCurrent()
		{
			_makeContextCurrent();
		}

		void Renderer::swapBuffers()
		{
			_swapBuffers();
		}

		void Renderer::release()
		{
			stop();
			_initialized = false;
		}

		bool Renderer::initialized()
		{
			return _initialized;
		}

		std::function<void()> const& Renderer::getExecutionProcedure()
		{
			return _procedure;
		}

		Core::ISystem& Renderer::getInterface()
		{
			return *this;
		}

		void Renderer::attachMakeContextCurrent(std::function<void()> const& operation)
		{
			assert(!_initialized);
			_makeContextCurrent = operation;
		}

		void Renderer::attachSwapBuffers(std::function<void()> const& operation)
		{
			assert(!_initialized);
			_swapBuffers = operation;
		}
	}
}