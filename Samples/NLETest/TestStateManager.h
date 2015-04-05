#ifndef TEST_STATE_MANAGER_H_
#define TEST_STATE_MANAGER_H_

#include "NLE\NLCore\NL_StateManager.h"
#include "NLE\NLCore\NL_DataDistributor.h"

class TestStateManager : public NLE::Core::StateManager
{
public:
	TestStateManager() :
		_floats(),
		_ints(),
		_chars()
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
		_floats.distribute();
		_ints.distribute();
		_chars.distribute();
	}

	NLE::Core::DataDistributor<float> _floats;
	NLE::Core::DataDistributor<int> _ints;
	NLE::Core::DataDistributor<char> _chars;

private:
};

#endif