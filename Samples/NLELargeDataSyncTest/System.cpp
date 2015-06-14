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
		/*Data data;
		for (unsigned int i = 0; i < shared.size(); ++i)
		{
			shared.modify(i, data);
		}*/
	};
}