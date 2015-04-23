#ifndef TEST_SYSTEM_H_
#define TEST_SYSTEM_H_

#include "NLE\NLCore\NL_System.h"
#include "NLE\NLCore\NL_SysState.h"
#include "NLE\NLCore\NL_SharedDataContainer.h"
#include "TestStateManager.h"
#include <memory>

class SysTask;
class Scheduler;
class StateManager;

class TestSysState : public NLE::Core::SysState
{
public:
	TestSysState()
	{
		printf("Created State.\n");
	}

	~TestSysState()
	{

	}

	bool initialize(uint_fast8_t sysId, 
		std::unique_ptr<NLE::Core::StateManager> const& stateManager)
	{
		TestStateManager* tsm = static_cast<TestStateManager*>(stateManager.get());

		return true;
	}

	void release()
	{

	}

	void update()
	{
		printf("Updating state.\n");

	}
private:
};


class TestSystem : public NLE::Core::System
{
public:
	TestSystem(NLE::Core::ExecutionType executionType, NLE::Core::Priority priority);
	~TestSystem();

	bool initialize(
		uint_fast8_t sysId,
		std::unique_ptr<NLE::Core::StateManager> const& stateManager);

	void release();
	NLE::Core::ExecutionDesc getExecutionDesc();
	uint_fast8_t getID();

	NLE::Core::SysTask* getTask(
		std::unique_ptr<NLE::Core::Scheduler> const& scheduler);

private:
	uint_fast8_t _id;
	TestSysState _sysState;
	NLE::Core::ExecutionType _execType;
	NLE::Core::Priority _priority;
};

#endif