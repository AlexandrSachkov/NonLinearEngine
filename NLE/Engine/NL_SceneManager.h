#ifndef NL_SCENE_MANAGER_H_
#define NL_SCENE_MANAGER_H_

#include "NL_ISceneManager.h"
#include "NL_RenderingResources.h"
#include "NL_GScene.h"
#include "NLCore\NL_System.h"
#include "NLCore\NL_Thread.h"

#include <functional>

#include "tbb\atomic.h"

struct lua_State;
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

		void setGScene(GRAPHICS::Scene* scene);
		GRAPHICS::Scene* getGScene();
	private:
		bool _initialized;
		std::wstring _path;
		std::function<void()> _procedure;
		Core::Thread _loadingThread;

		tbb::atomic<GRAPHICS::Scene*> _gScene;
		std::unique_ptr<IMPORTER::AssetImporter> _assetImporter;
	};
}


#endif