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
	TestSystem(uint_fast32_t id);
	~TestSystem();

	bool initialize(NLE::Core::IEngine& iEngine);

	void release();
	uint_fast32_t getID();

	std::function<void()> getExecutionProcedure();
	NLE::Core::ISystem* getInterface();

private:
	uint_fast32_t _id;
};

#endif