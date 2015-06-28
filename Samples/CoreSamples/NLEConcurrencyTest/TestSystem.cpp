#include "TestSystem.h"
#include "NLE\NLCore\NL_IEngine.h"
#include "SysInterface.h"

TestSystem::TestSystem(uint_fast32_t id) :
_id(id),
_initialized(false)
{
	_interface = new SysInterface(*this);
}

TestSystem::~TestSystem()
{

}

bool TestSystem::initialize(NLE::Core::IEngine& iEngine)
{
	_procedure = [&](){
		printf("Running task for system %i\n", getID());

		double num = 2000;
		for (int i = 0; i < 1000000000; i++)
		{
			num += sqrt(num) / 2;
		}

		printf("System %i finished with result %f\n", getID(), num);
	};

	_initialized = true;
	return true;
}

void TestSystem::release()
{

}

bool TestSystem::initialized()
{
	_initialized = false;
	return _initialized;
}

uint_fast32_t TestSystem::getID()
{
	return _id;
}

std::function<void()> const& TestSystem::getExecutionProcedure()
{
	return _procedure;
}

NLE::Core::ISystem& TestSystem::getInterface()
{
	return *_interface;
}