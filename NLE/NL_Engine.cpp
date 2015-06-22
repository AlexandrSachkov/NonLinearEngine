#include "NL_Engine.h"
#include "NLCore\NL_DeviceCore.h"
#include "NLCore\NL_ExecutionDesc.h"

#include "NLApplication\NL_Application.h"

#include <assert.h>
#include <memory>

namespace NLE
{
	Engine* Engine::_nle = nullptr;

	Engine::Engine() :
		_initialized(false)
	{
		Core::DeviceCore& core = Core::DeviceCore::instance();
		core.setClockPeriodNs(1000000L);

		Core::ExecutionDesc desc(
			NLE::Core::Priority::HIGH,
			NLE::Core::Execution::RECURRING,
			NLE::Core::Startup::AUTOMATIC,
			16666666L
		);

		core.attachSystem(0, desc, std::unique_ptr<Application>(new Application()));
	}

	Engine::~Engine()
	{
		release();
	}

	bool Engine::initialize()
	{
		assert(!_initialized);
		Core::DeviceCore::instance().initialize();

		_initialized = true;
		return true;
	}

	void Engine::release()
	{
		Core::DeviceCore::instance().release();
		_initialized = false;
	}

	void Engine::run()
	{
		assert(_initialized);
		Core::DeviceCore::instance().run();
	}

	void Engine::stop()
	{
		Core::DeviceCore::instance().stop();
	}
}
