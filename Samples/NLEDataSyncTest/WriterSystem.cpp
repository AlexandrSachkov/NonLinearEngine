#include "WriterSystem.h"
#include "TestStateManager.h"


WriterSystem::WriterSystem(NLE::Core::Priority priority) :
	_id(-1),
	_priority(priority),
	_addItem(true)
{

}

WriterSystem::~WriterSystem()
{

}

bool WriterSystem::initialize(
	uint_fast8_t id,
	std::unique_ptr<NLE::Core::StateManager> const& stateManager)
{
	_id = id;

	TestStateManager& stateMngr = *static_cast<TestStateManager*>(stateManager.get());
	_master = &stateMngr.msDistributor.buildMasterEndpoint(getID());
	_shared = &stateMngr.sDistributor.buildEndpoint(getID());

	return true;
}

void WriterSystem::release()
{

}

uint_fast8_t WriterSystem::getID()
{
	return _id;
}

NLE::Core::ExecutionDesc WriterSystem::getExecutionDesc()
{
	return {_priority, _id};
}

std::function<void()> WriterSystem::getExecutionProcedure()
{
	NLE::Core::Data::MasterContainer& master = *_master;
	NLE::Core::Data::SContainer& shared = *_shared;
	bool& addItem = _addItem;

	return [this, &master, &shared, &addItem](){
		for (unsigned int i = 0; i < shared.size(); ++i)
		{
			shared.modify(i, shared[i] + 1);
		}

		if (addItem)
		{
			master.add(10);
			if (master.size() == 10)
			{
				addItem = false;
			}
		}
		else
		{
			master.remove(0);
			if (master.size() == 0)
			{
				addItem = true;
			}
		}

		for (unsigned int i = 0; i < master.size(); i++)
		{
			master.modify(i, master[i] + 1);
		}
		
	};
}