#include "TestSysState.h"

#include "TestStateManager.h"

TestSysState::TestSysState()
{
	printf("Created State.\n");
}

TestSysState::~TestSysState()
{

}

bool TestSysState::initialize(uint_fast8_t sysId,
	std::unique_ptr<NLE::Core::StateManager> const& stateManager)
{
	TestStateManager* tsm = static_cast<TestStateManager*>(stateManager.get());

	return true;
}

void TestSysState::release()
{

}

void TestSysState::update()
{
	printf("Updating state.\n");

}