#include "ReaderSystem.h"
#include "SharedDataId.h"

ReaderSystem::ReaderSystem()
{

}

ReaderSystem::~ReaderSystem()
{

}

bool ReaderSystem::initialize(
	uint_fast8_t id,
	NLE::Core::StateManager* stateManager,
	NLE::Core::SysRuntimeControl& sysRuntimeControl)
{
	_id = id;

	_slave = &stateManager->getMSDistributor<double>(MS_CONTAINER).buildSlaveEndpoint(getID());
	_shared = &stateManager->getSDistributor<double>(S_CONTAINER).buildEndpoint(id);

	return true;
}

void ReaderSystem::release()
{

}

uint_fast8_t ReaderSystem::getID()
{
	return _id;
}

std::function<void()> ReaderSystem::getExecutionProcedure()
{
	NLE::Core::Data::SlaveContainer<double>& slave = *_slave;
	NLE::Core::Data::SContainer<double>& shared = *_shared;

	return [this, &slave, &shared](){
		printf("Reader #%i\n", getID());
		printf("SContainer:\n");
		for (unsigned int i = 0; i < shared.size(); ++i)
		{
			printf("%f\n", shared[i]);
		}
		printf("\n");

		printf("MSContainer:\n");
		for (unsigned int i = 0; i < slave.size(); ++i)
		{
			printf("%f\n", slave[i]);
		}
		printf("\n");
	};
}