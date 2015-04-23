#ifndef TEST_SYS_STATE_H_
#define TEST_SYS_STATE_H_

#include <cstdint>
#include <memory>

#include "NLE\NLCore\NL_DeviceCore.h"

class StateManager;

class TestSysState
{
public:
	TestSysState();
	~TestSysState();

	bool initialize(uint_fast8_t sysId,
		std::unique_ptr<NLE::Core::StateManager> const& stateManager);

	void release();
	void update();
};

#endif