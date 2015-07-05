#ifndef NL_RENDERING_ENGINE_H_
#define NL_RENDERING_ENGINE_H_

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
			bool initializeOpenGL();
			void release();

			void render();
		private:
		};
	}
}

#endif