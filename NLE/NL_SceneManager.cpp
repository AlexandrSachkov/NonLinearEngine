#include "NL_SceneManager.h"
#include "NL_AssetImporter.h"
#include "NL_IRenderingEngine.h"
#include "NL_Systems.h"
#include "NL_DeviceCore.h"
#include "NL_Console.h"
#include "NL_ThreadLocal.h"
#include "NL_SysInitializer.h"

#include <assert.h>

namespace NLE
{
	SceneManager::SceneManager() :
		_initialized(false),
		_procedure(nullptr),
		_loadingThread(100000L)
	{
		_assetImporter = std::make_unique<IMPORTER::AssetImporter>();
		_gScene.fetch_and_store(nullptr);
	}

	SceneManager::~SceneManager()
	{

	}

	bool SceneManager::initialize(Core::IEngine& engine, std::unique_ptr<Core::SysInitializer> const& initializer)
	{
		assert(!_initialized);

		_procedure = [&](){
			//load and unload objects as necessary
		};
		_initialized = true;
		return true;
	}

	void SceneManager::start()
	{

	}

	void SceneManager::stop()
	{

	}

	void SceneManager::release()
	{
		_initialized = false;
	}

	bool SceneManager::initialized()
	{
		return _initialized;
	}

	std::function<void()> const& SceneManager::getExecutionProcedure()
	{
		return _procedure;
	}

	Core::ISystem& SceneManager::getInterface()
	{
		return *this;
	}

	void SceneManager::setGScene(GRAPHICS::Scene* scene)
	{
		_gScene.fetch_and_store(scene);
	}

	GRAPHICS::Scene* SceneManager::getGScene()
	{
		return _gScene;
	}

	void SceneManager::importScene(std::wstring& path)
	{
		assert(_initialized && !_loadingThread.isRunning());

		_path = path;
		_loadingThread.setProcedure([&](){
			CONSOLE::out(CONSOLE::STANDARD, L"Loading Thread running");
			auto device = static_cast<GRAPHICS::IRenderingEngine*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERING_ENGINE))
				->getDevice();
			GRAPHICS::Scene* scene = new GRAPHICS::Scene();
			_assetImporter->importScene(device, _path, *scene);
			setGScene(scene);
			_loadingThread.stop();
		}, []() {});
		_loadingThread.start();
	}
}