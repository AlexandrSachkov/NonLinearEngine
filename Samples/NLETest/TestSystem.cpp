#include "TestSystem.h"
#include "NLE\NLCore\NL_SysTask.h"
#include "NLE\NLCore\NL_Scheduler.h"
#include "NLE\NLCore\NL_SysData.h"

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

NLE::Core::SysTask* TestSystem::getTask(
	std::unique_ptr<NLE::Core::Scheduler> const& scheduler,
	std::unique_ptr<NLE::Core::SysData> const& sysData)
{
	return new (tbb::task::allocate_root())NLE::Core::SysTask([this, &scheduler, &sysData](){
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