#ifndef NL_RENDERING_ENGINE_H_
#define NL_RENDERING_ENGINE_H_

#include "GL\glew.h"

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
			GLuint _program;
			GLuint _vertexArray;
		};
	}
}

#endif