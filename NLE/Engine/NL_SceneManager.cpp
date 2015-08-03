#include "NL_SceneManager.h"
#include "NL_AssetImporter.h"
#include "NL_IRenderer.h"
#include "NL_Systems.h"
#include "NLCore\NL_DeviceCore.h"

#include <assert.h>

namespace NLE
{
	SceneManager::SceneManager() :
		_initialized(false),
		_procedure(nullptr)
	{
		_assetImporter = std::make_unique<IMPORTER::AssetImporter>();
	}

	SceneManager::~SceneManager()
	{

	}

	bool SceneManager::initialize(Core::IEngine& engine)
	{
		assert(!_initialized);

		_procedure = [&](){
			//load and unload objects as necessary
		};
		_initialized = true;
		return true;
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

	bool SceneManager::importScene(std::wstring& path)
	{
		assert(_initialized);
		auto device = static_cast<GRAPHICS::IRenderer*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERER))
			->getDevice();
		return _assetImporter->importAssets(device, path, this);
	}

	void SceneManager::addStaticRenderable(GRAPHICS::RESOURCES::Renderable& renderable)
	{
		static_cast<GRAPHICS::IRenderer*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERER))
			->addStaticRenderable(renderable);
	}

	void SceneManager::addLight(GRAPHICS::RESOURCES::Light& light)
	{
		static_cast<GRAPHICS::IRenderer*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERER))
			->addLight(light);
	}
}