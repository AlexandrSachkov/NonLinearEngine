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
	TestSystem();
	~TestSystem();

	bool initialize(
		uint_fast32_t sysId,
		NLE::Core::IEngine& iEngine);

	void release();
	uint_fast32_t getID();

	std::function<void()> getExecutionProcedure();

private:
	uint_fast32_t _id;
};

#endif