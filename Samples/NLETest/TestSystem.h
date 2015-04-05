#ifndef TEST_SYSTEM_H_
#define TEST_SYSTEM_H_

#include "NLE\NLCore\NL_System.h"
#include "NLE\NLCore\NL_SysState.h"
#include <memory>

class SysTask;
class Scheduler;

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

	void update()
	{

	}

private:
};


class TestSystem : public NLE::Core::System
{
public:
	TestSystem();
	~TestSystem();

	bool initialize(uint_fast8_t id);
	void release();

	uint_fast8_t getID();

	NLE::Core::SysTask* getTask(
		std::unique_ptr<NLE::Core::Scheduler> const& scheduler);

private:
	uint_fast8_t _id;
	TestSysState _sysState;
};

#endif