#ifndef TEST_STATE_MANAGER_H_
#define TEST_STATE_MANAGER_H_

#include <cstdio>
#include "NLE\NLCore\NL_StateManager.h"

class TestStateManager : public NLE::Core::StateManager
{
public:
	TestStateManager()
	{

	}

	~TestStateManager()
	{

	}

	bool initialize()
	{
		return true;
	}

	void release()
	{

	}

	void processRequests()
	{
		printf("Processing requests\n");

	}

	void distributeFrom(uint_fast8_t sysId)
	{
		printf("Distributing from %i\n", sysId);
	}

	void distributeTo(uint_fast8_t sysId)
	{
		printf("Distributing to %i\n", sysId);
	}

private:
};

#endif