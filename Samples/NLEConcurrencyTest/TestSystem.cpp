#include "TestSystem.h"
#include "NLE\NLCore\NL_StateManager.h"

TestSystem::TestSystem(uint_fast32_t id) :
_id(id)
{

}

TestSystem::~TestSystem()
{

}

bool TestSystem::initialize(NLE::Core::IEngine& iEngine)
{
	return true;
}

void TestSystem::release()
{

}

uint_fast32_t TestSystem::getID()
{
	return _id;
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