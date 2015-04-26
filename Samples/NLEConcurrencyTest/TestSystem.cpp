#include "TestSystem.h"
#include "NLE\NLCore\NL_StateManager.h"

TestSystem::TestSystem(NLE::Core::Priority priority) :
	_id(-1),
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
	return {_priority, _id};
}

std::function<void()> TestSystem::getExecutionProcedure()
{
	return [this](){
		printf("Running task for system %i\n", getID());

		double num = 2000;
		for (int i = 0; i < 1000000000; i++)
		{
			num += sqrt(num) / 2;
		}

		printf("System %i finished with result %f\n", getID(), num);
	};
}