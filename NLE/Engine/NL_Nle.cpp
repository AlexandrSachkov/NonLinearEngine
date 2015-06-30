#include "NL_Nle.h"

#include "NLCore\NL_DeviceCore.h"
#include "NLCore\NL_ExecutionDesc.h"
#include "NL_InputEvents.h"
#include "NL_InputProcessor.h"
#include "NL_Systems.h"

#include <assert.h>
#include <memory>

namespace NLE
{
	Nle* Nle::_nle = nullptr;

	Nle::Nle() :
		_initialized(false)
	{
		Core::DeviceCore& core = Core::DeviceCore::instance();
		core.setClockPeriodNs(1000000L);

		Core::ExecutionDesc inputProcDesc(
			Core::Priority::HIGH,
			Core::Execution::RECURRING,
			Core::Mode::SYNC,
			Core::Startup::AUTOMATIC,
			16666666L	//60 FPS
		);

		core.attachSystem(SYS::SYS_INPUT_PROCESSOR, inputProcDesc, std::unique_ptr<INPUT::InputProcessor>(new INPUT::InputProcessor()));
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
	}

	void Nle::run()
	{
		assert(_initialized);
		Core::DeviceCore::instance().run();
	}

	void Nle::stop()
	{
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
}
