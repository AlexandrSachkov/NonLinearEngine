#include "System.h"
#include "Data.h"

System::System()
{

}

System::~System()
{

}

bool System::initialize(
	uint_fast32_t id,
	NLE::Core::IEngine& iEngine)
{
	_id = id;
	_iEngine = &iEngine;
	_shared = &iEngine.getSDistributor<Data>(id).buildEndpoint(id);
	_operation = [&](){
		printf("Running task for system %i\n", getID());
		Data data;
		auto start = std::chrono::high_resolution_clock::now();
		for (unsigned int i = 0; i < _shared->size(); ++i)
		{
			_shared->modify(i, data);
		}
		auto end = std::chrono::high_resolution_clock::now();
		printf("Modify: %f\n", std::chrono::duration <double, std::micro>(end - start).count());
	};
	return true;
}

void System::release()
{

}

uint_fast32_t System::getID()
{
	return _id;
}

std::function<void()> System::getExecutionProcedure()
{
	NLE::Core::Data::SContainer<Data>& shared = *_shared;

	return _operation;
}