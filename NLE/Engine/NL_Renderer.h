#ifndef NL_RENDERER_H_
#define NL_RENDERER_H_

#include "NL_IRenderer.h"
#include "NLCore\NL_System.h"

#include "tbb\atomic.h"

#include <functional>
#include <thread>

namespace NLE
{
	namespace Core
	{
		class IEngine;
		class ISystem;
	}

	namespace GRAPHICS
	{
		class RenderingEngine;
		class Renderer : public Core::System, public IRenderer
		{
		public:
			Renderer();
			~Renderer();

			bool initialize(Core::IEngine& engine);
			void release();

			bool initialized();
			bool isRunning();

			void setWindowHandle(void* handle);
			void setScreenDimensions(uint_fast32_t width, uint_fast32_t height);
			void setFullscreen(bool fullscreen);
			void stop();

			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();

		private:
			bool _initialized;
			tbb::atomic<bool> _running;
			std::function<void()> _procedure;

			std::thread* _renderingThread;
			std::unique_ptr<RenderingEngine> _renderingEngine;
		};
	}
}

#endif