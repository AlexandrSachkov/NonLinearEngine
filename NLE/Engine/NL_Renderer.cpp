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
			assert(!_initialized);

			if (!_renderingEngine->initialize())
				return false;

			_procedure = [&](){
				printf("Starting Rendering task\n");

				_running.fetch_and_store(true);
				_renderingThread = new std::thread([&](Renderer& renderer, std::unique_ptr<RenderingEngine> const& renderingEngine){

					printf("Rendering Thread running\n");			
					while (renderer.isRunning())
					{
						renderingEngine->render();
					}
				}, std::ref(*this), std::ref(_renderingEngine));
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

		void Renderer::setWindowHandle(void* handle)
		{
			_renderingEngine->setWindowHandle(handle);
		}

		void Renderer::setScreenDimensions(uint_fast32_t width, uint_fast32_t height)
		{
			_renderingEngine->setScreenDimensions(width, height);
		}

		void Renderer::setFullscreen(bool fullscreen)
		{
			_renderingEngine->setFullscreen(fullscreen);
		}
	}
}