#include "System.h"
#include "Data.h"

System::System(uint_fast32_t id) : _id(id)
{

}

System::~System()
{

}

bool System::initialize(NLE::Core::IEngine& iEngine)
{
	_iEngine = &iEngine;
	_shared = &iEngine.getSDistributor<Data>(_id).buildEndpoint(_id);
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
	return true;
}

void System::release()
{

}

std::function<void()> System::getExecutionProcedure()
{
	NLE::Core::Data::SContainer<Data>& shared = *_shared;

	return _operation;
}