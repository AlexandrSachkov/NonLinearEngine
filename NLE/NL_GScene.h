#ifndef NL_GSCENE_H_
#define NL_GSCENE_H_

#include "NL_RenderingResources.h"
#include "tbb\atomic.h"
#include <vector>

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
			void addDirectionalLight(RESOURCES::DirectionalLight& light);
			void addSpotLight(RESOURCES::SpotLight& light);
			void addPointLight(RESOURCES::PointLight& light);
			void recompileBuffers(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

			std::vector<RESOURCES::Renderable> const& getStaticOpaqueRenderables();
			RESOURCES::Buffer getLightBuffer();
		private:
			RESOURCES::Buffer _lightBuff;
			RESOURCES::LightBuff _lights;
			tbb::atomic<bool> _pendingUpdate;
			std::vector<RESOURCES::Renderable> _staticOpaqueRenderables;
		};
	}
}

#endif