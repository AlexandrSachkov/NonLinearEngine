#ifndef NL_GSCENE_H_
#define NL_GSCENE_H_

#include "NL_RenderingResources.h"

#include "tbb\concurrent_vector.h"
namespace NLE
{
	namespace GRAPHICS
	{
		class Scene
		{
		public:
			Scene();
			~Scene();

			void release();

			void addStaticRenderable(RESOURCES::Renderable& renderable);
			void addLight(RESOURCES::Light& light);

			tbb::concurrent_vector<RESOURCES::Renderable> const& getStaticOpaqueRenderables();
		private:
			tbb::concurrent_vector<RESOURCES::Renderable> _staticOpaqueRenderables;
			tbb::concurrent_vector<RESOURCES::Light> _lights;
		};
	}
}

#endif