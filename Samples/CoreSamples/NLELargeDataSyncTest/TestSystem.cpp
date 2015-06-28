#include "TestSystem.h"
#include "Data.h"
#include "NLE\NLCore\NL_IEngine.h"

TestSystem::TestSystem(uint_fast32_t id) : 
_id(id), 
_initialized(false)
{

}

TestSystem::~TestSystem()
{

}

bool TestSystem::initialize(NLE::Core::IEngine& iEngine)
{
	_iEngine = &iEngine;
	_shared = &iEngine.getSDistributor<Data>(_id).buildEndpoint(_id);

	if (_id + 1 == iEngine.getNumHardwareThreads())
		_sharedReader = &iEngine.getSDistributor<Data>(0).buildEndpoint(_id);
	else
		_sharedReader = &iEngine.getSDistributor<Data>(_id + 1).buildEndpoint(_id);

	_operation = [&](){
		printf("Running task for system %i\n", _id);
		Data data;
		auto start = std::chrono::high_resolution_clock::now();
		for (unsigned int i = 0; i < _shared->size(); ++i)
		{
			_shared->modify(i, data);
		}
		auto end = std::chrono::high_resolution_clock::now();
		printf("Modify: %f\n", std::chrono::duration <double, std::micro>(end - start).count());
	};

	_initialized = true;
	return true;
}

void TestSystem::release()
{
	_initialized = false;
}

bool TestSystem::initialized()
{
	return _initialized;
}

std::function<void()> const& TestSystem::getExecutionProcedure()
{
	return _operation;
}

NLE::Core::ISystem& TestSystem::getInterface()
{
	return *this;
}