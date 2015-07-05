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
			void stop();
			void makeContextCurrent();
			void swapBuffers();
			void configureVSync();

			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();

			void attachMakeContextCurrent(std::function<void()> const& operation);
			void attachSwapBuffers(std::function<void()> const& operation);
			void attachConfigureVSync(std::function<void()> const& operation);

		private:
			bool _initialized;
			tbb::atomic<bool> _running;
			std::function<void()> _procedure;
			std::function<void()> _makeContextCurrent;
			std::function<void()> _swapBuffers;
			std::function<void()> _configureVSync;
			std::thread* _renderingThread;
			std::unique_ptr<RenderingEngine> _renderingEngine;
		};
	}
}

#endif