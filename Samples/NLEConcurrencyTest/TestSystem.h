#ifndef TEST_SYSTEM_H_
#define TEST_SYSTEM_H_

#include "NLE\NLCore\NL_System.h"
#include <memory>

class SysTask;
class Scheduler;
class StateManager;


class TestSystem : public NLE::Core::System
{
public:
	TestSystem(NLE::Core::Priority priority);
	~TestSystem();

	bool initialize(
		uint_fast8_t sysId,
		std::unique_ptr<NLE::Core::StateManager> const& stateManager);

	void release();
	NLE::Core::ExecutionDesc getExecutionDesc();
	uint_fast8_t getID();

	std::function<void()> getExecutionProcedure();

private:
	uint_fast8_t _id;
	NLE::Core::Priority _priority;
};

#endif