#ifndef TEST_STATE_MANAGER_H_
#define TEST_STATE_MANAGER_H_

#include "NLE\NLCore\NL_StateManager.h"
#include "NLE\NLCore\NL_DataDistributor.h"

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

	void distributeData()
	{
		printf("Distributing data\n");

	}

private:
};

#endif