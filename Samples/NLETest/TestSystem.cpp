#include "TestSystem.h"
#include "NLE\NLCore\NL_SysTask.h"
//#include <math.h>

TestSystem::TestSystem(int id) : _id(id)
{

}

TestSystem::~TestSystem()
{

}

int TestSystem::getID()
{
	return _id;
}

NLE::Core::SysTask* TestSystem::getTask()
{
	return new (tbb::task::allocate_root())NLE::Core::SysTask(nullptr, [this](){
		//printf("Running task for system %i\n", getID());
		double num = 2000;
		for (int i = 0; i < 100000000; i++)
		{
			num += sqrt(num) / 2;
		}
		//printf("Finishing task for system %i\n", getID());
		return nullptr;
	});
}