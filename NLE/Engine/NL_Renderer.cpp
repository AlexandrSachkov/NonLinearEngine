#include "NL_Renderer.h"
#include "NLCore\NL_ISystem.h"
#include "NLCore\NL_IEngine.h"
#include "NL_RenderingEngine.h"

#include <assert.h>

namespace NLE
{
	namespace GRAPHICS
	{
		Renderer::Renderer() :
			_initialized(false)
		{
			_running.fetch_and_store(false);
			_renderingEngine = std::make_unique<RenderingEngine>();
		}

		Renderer::~Renderer()
		{

		}

		bool Renderer::initialize(Core::IEngine& engine)
		{
			assert(!_initialized && _makeContextCurrent && _swapBuffers && _configureVSync);

			_procedure = [&](){
				printf("Starting Rendering task\n");

				_running.fetch_and_store(true);
				_renderingThread = new std::thread([&](Renderer& renderer, std::unique_ptr<RenderingEngine> const& renderingEngine){

					printf("Rendering Thread running\n");			
					renderer.makeContextCurrent();
					renderer.configureVSync();

					if (!renderingEngine->initializeOpenGL())
					{
						printf("OpenGL failed to initialize");
						return;
					}						

					while (renderer.isRunning())
					{
						renderingEngine->render();
						renderer.swapBuffers();
					}
				}, std::ref(*this), std::ref(_renderingEngine));
			};

			if (!_renderingEngine->initialize())
				return false;

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

		void Renderer::configureVSync()
		{
			_configureVSync();
		}

		void Renderer::release()
		{
			stop();
			_renderingEngine->release();
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

		void Renderer::attachConfigureVSync(std::function<void()> const& operation)
		{
			assert(!_initialized);
			_configureVSync = operation;
		}
	}
}