#include "NL_Nle.h"

#include "NLCore\NL_DeviceCore.h"
#include "NLCore\NL_ExecutionDesc.h"
#include "NL_InputEvents.h"
#include "NL_InputProcessor.h"
#include "NL_SceneManager.h"
#include "NL_Renderer.h"
#include "NL_Systems.h"
#include "NL_SharedContainers.h"

#include <assert.h>
#include <memory>

namespace NLE
{
	Nle* Nle::_nle = nullptr;

	Nle::Nle() :
		_initialized(false),
		_defaultGrainSize(6500)
	{
		Core::DeviceCore& core = Core::DeviceCore::instance();
		core.setClockPeriodNs(1000000L);

		// Install shared containers
		core.installSContainer<char>(CAMERA_COMMANDS, GRAPHICS::COMMANDS::CAMERA::NUM_COMMANDS, _defaultGrainSize); //one slot for each command
		core.installSContainer<double>(CURSOR_COORDINATES, 2, _defaultGrainSize);	// 2 slots for x and y components
		core.installSContainer<double>(SCROLL_OFFSET, 2, _defaultGrainSize);	// 2 slots for x and y components

		// Attach systems
		Core::ExecutionDesc inputProcDesc(
			Core::Priority::HIGH,
			Core::Execution::RECURRING,
			Core::Mode::SYNC,
			Core::Startup::AUTOMATIC,
			16666666L	//60 FPS
		);
		core.attachSystem(SYS::SYS_INPUT_PROCESSOR, inputProcDesc, std::unique_ptr<INPUT::InputProcessor>(new INPUT::InputProcessor()));

		core.setNumThreads(core.getNumThreads() - 1); // Leave a hardware thread for graphics
		Core::ExecutionDesc renderingProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::RECURRING,
			Core::Mode::ASYNC ,
			Core::Startup::AUTOMATIC,
			16666666L	//60 FPS
		);
		core.attachSystem(SYS::SYS_RENDERER, renderingProcDesc, std::unique_ptr<GRAPHICS::Renderer>(new GRAPHICS::Renderer()));

		Core::ExecutionDesc sceneMngrProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::RECURRING,
			Core::Mode::ASYNC,
			Core::Startup::AUTOMATIC,
			1000000000L	//1 FPS
		);
		core.attachSystem(SYS::SYS_SCENE_MANAGER, sceneMngrProcDesc, std::unique_ptr<SceneManager>(new SceneManager()));
	}

	Nle::~Nle()
	{
		release();
	}

	bool Nle::initialize()
	{
		assert(!_initialized);
		if (!Core::DeviceCore::instance().initialize())
			return false;

		_initialized = true;
		return true;
	}

	void Nle::release()
	{
		Core::DeviceCore::instance().release();
		_initialized = false;
		delete this;
	}

	void Nle::run()
	{
		assert(_initialized);
		Core::DeviceCore::instance().run();
	}

	void Nle::stop()
	{
		static_cast<GRAPHICS::IRenderer*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERER))
			->stop();
		Core::DeviceCore::instance().stop();
	}

	void Nle::attachPollEvents(std::function<void()> const& operation)
	{
		static_cast<INPUT::IInputProcessor*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_INPUT_PROCESSOR))
			->attachPollEvents(operation);
	}

	void Nle::processEvent(INPUT::Event& event)
	{
		static_cast<INPUT::IInputProcessor*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_INPUT_PROCESSOR))
			->processEvent(event);
	}

	void Nle::setWindowHandle(void* handle)
	{
		static_cast<GRAPHICS::IRenderer*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERER))
			->setWindowHandle(handle);
	}

	void Nle::setScreenDimensions(uint_fast32_t width, uint_fast32_t height)
	{
		static_cast<GRAPHICS::IRenderer*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERER))
			->setScreenDimensions(width, height);
	}

	void Nle::setFullscreen(bool fullscreen)
	{
		static_cast<GRAPHICS::IRenderer*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERER))
			->setFullscreen(fullscreen);
	}

	bool Nle::importScene(std::wstring& path)
	{
		return static_cast<SceneManager*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_SCENE_MANAGER))
			->importScene(path);
	}
}
