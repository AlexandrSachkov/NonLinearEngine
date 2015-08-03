#include "NL_GScene.h"

namespace NLE
{
	namespace GRAPHICS
	{
		Scene::Scene()
		{

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

		void Scene::addLight(RESOURCES::Light& light)
		{
			_lights.push_back(light);
		}

		tbb::concurrent_vector<RESOURCES::Renderable> const& Scene::getStaticOpaqueRenderables()
		{
			return _staticOpaqueRenderables;
		}
	}
}