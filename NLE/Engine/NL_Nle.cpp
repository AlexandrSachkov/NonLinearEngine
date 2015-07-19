#include "NL_Nle.h"

#include "NLCore\NL_DeviceCore.h"
#include "NLCore\NL_ExecutionDesc.h"
#include "NL_InputEvents.h"
#include "NL_InputProcessor.h"
#include "NL_CameraController.h"
#include "NL_Renderer.h"
#include "NL_Systems.h"
#include "NL_SharedContainers.h"

#include "glm\mat4x4.hpp"

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
		core.installSContainer<char>(CAMERA_CONTROLLER_COMMANDS, CAMERA::COMMANDS::NUM_COMMANDS, _defaultGrainSize); //one slot for each command
		core.installSContainer<double>(CURSOR_COORDINATES, 2, _defaultGrainSize);	// 2 slots for x and y components
		core.installSContainer<double>(SCROLL_OFFSET, 2, _defaultGrainSize);	// 2 slots for x and y components
		core.installSContainer<glm::mat4x4>(VIEW_PROJECTION, 2, _defaultGrainSize);

		// Attach systems
		Core::ExecutionDesc inputProcDesc(
			Core::Priority::HIGH,
			Core::Execution::RECURRING,
			Core::Mode::SYNC,
			Core::Startup::AUTOMATIC,
			16666666L	//60 FPS
		);
		core.attachSystem(SYS::SYS_INPUT_PROCESSOR, inputProcDesc, std::unique_ptr<INPUT::InputProcessor>(new INPUT::InputProcessor()));
		core.attachSystem(SYS::SYS_CAMERA_CONTROLLER, inputProcDesc, std::unique_ptr<CAMERA::CameraController>(new CAMERA::CameraController()));

		core.setNumThreads(core.getNumThreads() - 1); // Leave a hardware thread for graphics
		Core::ExecutionDesc renderingProcDesc(
			Core::Priority::STANDARD,
			Core::Execution::SINGULAR,
			Core::Mode::SYNC ,
			Core::Startup::AUTOMATIC,
			0
		);
		core.attachSystem(SYS::SYS_RENDERER, renderingProcDesc, std::unique_ptr<GRAPHICS::Renderer>(new GRAPHICS::Renderer()));
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

	void Nle::attachMakeContextCurrent(std::function<void()> const& operation)
	{
		static_cast<GRAPHICS::IRenderer*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERER))
			->attachMakeContextCurrent(operation);
	}

	void Nle::attachSwapBuffers(std::function<void()> const& operation)
	{
		static_cast<GRAPHICS::IRenderer*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERER))
			->attachSwapBuffers(operation);
	}

	void Nle::attachConfigureVSync(std::function<void()> const& operation)
	{
		static_cast<GRAPHICS::IRenderer*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_RENDERER))
			->attachConfigureVSync(operation);
	}

	void Nle::setScreenDimensions(uint_fast32_t width, uint_fast32_t height)
	{
		static_cast<CAMERA::ICameraController*>(&Core::DeviceCore::instance().getSystemInterface(SYS::SYS_CAMERA_CONTROLLER))
			->setScreenDimensions(width, height);
	}
}
