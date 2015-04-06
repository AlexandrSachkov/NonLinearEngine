#ifndef TEST_SYSTEM_H_
#define TEST_SYSTEM_H_

#include "NLE\NLCore\NL_System.h"
#include "NLE\NLCore\NL_SysState.h"
#include "NLE\NLCore\NL_DataContainer.h"
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

		printf("Initializing state.\n");
		_myFloats.initialize(sysId, 10);
		tsm->_floats.bindContainer(&_myFloats);

		_myInts.initialize(sysId, 10);
		tsm->_ints.bindContainer(&_myInts);

		_myChars.initialize(sysId, 10);
		tsm->_chars.bindContainer(&_myChars);

		return true;
	}

	void release()
	{
		_myFloats.release();
		_myInts.release();
		_myChars.release();
	}

	void update()
	{
		printf("Updating state.\n");
		_myFloats.applyUpdates();
		_myInts.applyUpdates();
		_myChars.applyUpdates();
	}

	NLE::Core::DataContainer<float> _myFloats;
	NLE::Core::DataContainer<int> _myInts;
	NLE::Core::DataContainer<char> _myChars;
private:
};


class TestSystem : public NLE::Core::System
{
public:
	TestSystem();
	~TestSystem();

	bool initialize(
		uint_fast8_t sysId,
		std::unique_ptr<NLE::Core::StateManager> const& stateManager);

	void release();

	uint_fast8_t getID();

	NLE::Core::SysTask* getTask(
		std::unique_ptr<NLE::Core::Scheduler> const& scheduler);

private:
	uint_fast8_t _id;
	TestSysState _sysState;
};

#endif