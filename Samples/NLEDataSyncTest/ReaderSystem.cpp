#include "ReaderSystem.h"
#include "TestStateManager.h"

ReaderSystem::ReaderSystem()
{

}

ReaderSystem::~ReaderSystem()
{

}

bool ReaderSystem::initialize(
	uint_fast8_t id,
	std::unique_ptr<NLE::Core::StateManager> const& stateManager)
{
	_id = id;

	TestStateManager& stateMngr = *static_cast<TestStateManager*>(stateManager.get());
	_slave = &stateMngr.msDistributor.buildSlaveEndpoint(getID());
	_shared = &stateMngr.sDistributor.buildEndpoint(getID());

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
	NLE::Core::Data::SlaveContainer& slave = *_slave;
	NLE::Core::Data::SContainer& shared = *_shared;

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