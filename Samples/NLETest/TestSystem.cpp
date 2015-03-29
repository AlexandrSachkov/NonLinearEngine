#include "TestSystem.h"
#include "NLE\NLCore\NL_SysTask.h"
#include "NLE\NLCore\NL_Scheduler.h"

TestSystem::TestSystem() : _id(-1)
{

}

TestSystem::~TestSystem()
{

}

bool TestSystem::initialize(uint_fast8_t id)
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

NLE::Core::SysTask* TestSystem::getTask(NLE::Core::Scheduler* scheduler)
{
	return new (tbb::task::allocate_root())NLE::Core::SysTask([this, scheduler](){
		printf("Running task for system %i\n", getID());
		double num = 2000;
		for (int i = 0; i < 1000000000; i++)
		{
			num += sqrt(num) / 2;
		}
		//printf("Finishing task for system %i\n", getID());
		scheduler->scheduleExecution(getID());

		printf("Restarting task %i with result %f\n", getID(), num);
		return nullptr;
	});
}