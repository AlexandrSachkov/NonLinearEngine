#include "TestSystem.h"
#include "NLE\NLCore\NL_SysTask.h"
#include "NLE\NLCore\NL_Scheduler.h"
#include "NLE\NLCore\NL_StateManager.h"

TestSystem::TestSystem(NLE::Core::ExecutionType executionType, NLE::Core::Priority priority) :
	_id(-1),
	_sysState(),
	_execType(executionType),
	_priority(priority)
{

}

TestSystem::~TestSystem()
{

}

bool TestSystem::initialize(
	uint_fast8_t id,
	std::unique_ptr<NLE::Core::StateManager> const& stateManager)
{
	_id = id;
	if (!_sysState.initialize(id, stateManager))
		return false;
	return true;
}

void TestSystem::release()
{

}

uint_fast8_t TestSystem::getID()
{
	return _id;
}

NLE::Core::ExecutionDesc TestSystem::getExecutionDesc()
{
	return {_execType, _priority, _id};
}

NLE::Core::SysTask* TestSystem::getTask(std::unique_ptr<NLE::Core::Scheduler> const& scheduler)
{
	TestSysState& testSysState = _sysState;
	return new (tbb::task::allocate_root())NLE::Core::SysTask([this, &scheduler, &testSysState](){
		printf("Running task for system %i\n", getID());
		testSysState.update();

		double num = 2000;
		for (int i = 0; i < 1000000000; i++)
		{
			num += sqrt(num) / 2;
		}

		//printf("Finishing task for system %i\n", getID());
		scheduler->scheduleExecution(getExecutionDesc());

		printf("Restarting task %i with result %f\n", getID(), num);
		return nullptr;
	});
}