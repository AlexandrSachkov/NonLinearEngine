#ifndef NL_SCENE_MANAGER_H_
#define NL_SCENE_MANAGER_H_

#include "NL_ISceneManager.h"
#include "NL_RenderingResources.h"
#include "NLCore\NL_System.h"

#include <functional>
#include <thread>

namespace NLE
{
	namespace GRAPHICS
	{
		class Scene;
	}
	namespace IMPORTER
	{
		class AssetImporter;
	}

	class SceneManager : public Core::System, public ISceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		bool initialize(Core::IEngine& engine);
		void release();

		bool initialized();
		std::function<void()> const& getExecutionProcedure();
		Core::ISystem& getInterface();

		void importScene(std::wstring& path);
		void addStaticRenderable(GRAPHICS::RESOURCES::Renderable& renderable);
		void addLight(GRAPHICS::RESOURCES::Light& light);

	private:
		bool _initialized;
		std::function<void()> _procedure;
		std::thread* _loadingThread;

		std::unique_ptr<IMPORTER::AssetImporter> _assetImporter;
	};
}


#endif