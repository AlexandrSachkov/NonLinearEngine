#include "NL_GScene.h"
#include "NL_D3D11Utility.h"


namespace NLE
{
	namespace GRAPHICS
	{
		Scene::Scene()
		{
			_pendingUpdate.fetch_and_store(true);
		}

		Scene::~Scene()
		{

		}

		void Scene::release()
		{
			for (auto renderable : _staticOpaqueRenderables)
			{
				renderable.release();
			}
		}

		void Scene::addStaticRenderable(RESOURCES::Renderable& renderable)
		{
			_staticOpaqueRenderables.push_back(renderable);
		}


		tbb::concurrent_vector<RESOURCES::Renderable> const& Scene::getStaticOpaqueRenderables()
		{
			return _staticOpaqueRenderables;
		}

		void Scene::update(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
		{
			if (_pendingUpdate)
			{
				/*if (_lightBuff.apiBuffer == nullptr)
				{
					GRAPHICS::D3D11Utility::createBuffer<GRAPHICS::RESOURCES::DirectionalLightBuff>(
						device, 
						D3D11_BIND_CONSTANT_BUFFER, 
						D3D11_USAGE_IMMUTABLE, 
						&_directionalLights[0], 
						_directionalLights.size(), 
						_dirLightBuff
					);
				}
				else
				{
					GRAPHICS::D3D11Utility::updateBuffer(deviceContext, _dirLightBuff, &_directionalLights[0], _directionalLights.size());
				}*/
				_pendingUpdate.fetch_and_store(false);
			}
		}
	}
}