#include "System.h"
#include "Data.h"

System::System()
{

}

System::~System()
{

}

bool System::initialize(
	uint_fast8_t id,
	NLE::Core::StateManager* stateManager,
	NLE::Core::SysRuntimeControl& sysRuntimeControl)
{
	_id = id;
	_sysRuntimeControl = &sysRuntimeControl;
	_shared = &stateManager->getSDistributor<Data>(id).buildEndpoint(id);

	return true;
}

void System::release()
{

}

uint_fast8_t System::getID()
{
	return _id;
}

std::function<void()> System::getExecutionProcedure()
{
	NLE::Core::Data::SContainer<Data>& shared = *_shared;

	return [this, &shared](){
		printf("Running task for system %i\n", getID());
		Data data;
		auto start = std::chrono::high_resolution_clock::now();
		for (unsigned int i = 0; i < shared.size(); ++i)
		{
			shared.modify(i, data);
		}
		auto end = std::chrono::high_resolution_clock::now();
		printf("Modify: %f\n", std::chrono::duration <double, std::micro>(end - start).count());
	};
}