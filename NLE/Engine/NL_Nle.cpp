#include "NL_Nle.h"

#include "NLCore\NL_DeviceCore.h"
#include "NLCore\NL_ExecutionDesc.h"
#include "NL_Application.h"
#include "NL_InputEvents.h"

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

		Core::ExecutionDesc desc(
			NLE::Core::Priority::HIGH,
			NLE::Core::Execution::RECURRING,
			NLE::Core::Startup::AUTOMATIC,
			16666666L	//60 FPS
		);

		core.attachSystem(0, desc, std::unique_ptr<Application>(new Application()));
	}

	Nle::~Nle()
	{
		release();
	}

	bool Nle::initialize()
	{
		assert(!_initialized);
		Core::DeviceCore::instance().initialize();

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

	void Nle::attachEventPollingOperation(std::function<void()> operation)
	{
		Core::DeviceCore::instance().attachUITheadOperation(0L, operation);
	}

	void Nle::processEvent(INPUT::Event& event)
	{

	}
}
