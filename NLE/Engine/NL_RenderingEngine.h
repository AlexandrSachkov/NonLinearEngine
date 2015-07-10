#ifndef NL_RENDERING_ENGINE_H_
#define NL_RENDERING_ENGINE_H_

#include "GL\glew.h"
#include <cstdint>
#include <chrono>

namespace NLE
{
	namespace GRAPHICS
	{
		class RenderingEngine
		{
		public:
			RenderingEngine();
			~RenderingEngine();

			bool initialize();
			bool initializeOpenGL(); // must be called from the rendering thread
			void release();

			void render();

		private:
			uint_fast32_t _frameCount;
			std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> _previousTime;
			GLuint _program;
			GLuint _vertexArray;
		};
	}
}

#endif