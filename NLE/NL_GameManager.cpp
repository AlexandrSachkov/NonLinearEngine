#include "NL_GameManager.h"
#include "NL_IRenderingEngine.h"
#include "NL_Systems.h"
#include "NL_DeviceCore.h"
#include "NL_Console.h"
#include "NL_ThreadLocal.h"
#include "NL_SysInitializer.h"

#include <assert.h>

namespace NLE
{
	GameManager::GameManager() :
		_initialized(false),
		_procedure(nullptr),
		_loadingThread(100000L)
	{
		_gScene.fetch_and_store(nullptr);
	}

	GameManager::~GameManager()
	{

	}

	bool GameManager::initialize(Core::IEngine& engine, std::unique_ptr<Core::SysInitializer> const& initializer)
	{
		assert(!_initialized);

		_procedure = [&](){
			//load and unload objects as necessary
		};
		_initialized = true;
		return true;
	}

	void GameManager::start()
	{

	}

	void GameManager::stop()
	{

	}

	void GameManager::release()
	{
		_initialized = false;
	}

	bool GameManager::initialized()
	{
		return _initialized;
	}

	std::function<void()> const& GameManager::getExecutionProcedure()
	{
		return _procedure;
	}

	Core::ISystem& GameManager::getInterface()
	{
		return *this;
	}

	void GameManager::setGScene(GRAPHICS::Scene* scene)
	{
		_gScene.fetch_and_store(scene);
	}

	GRAPHICS::Scene* GameManager::getGScene()
	{
		return _gScene;
	}

	void GameManager::importScene(std::wstring& path)
	{
		assert(_initialized && !_loadingThread.isRunning());

		_path = path;
		_loadingThread.setProcedure([&](){
			CONSOLE::out(CONSOLE::STANDARD, L"Loading Thread running");
			//GRAPHICS::Scene* scene = new GRAPHICS::Scene();
			//_assetImporter->importScene(device, _path, *scene);
			//setGScene(scene);
			_loadingThread.stop();
		}, []() {});
		_loadingThread.start();
	}
}