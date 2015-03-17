#include "TestSystem.h"

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

tbb::task* TestSystem::execute()
{
	printf("Executing system: %i\n", getID());
	return nullptr;
}