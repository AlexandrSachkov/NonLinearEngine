#include "WriterSystem.h"
#include "SharedDataId.h"


WriterSystem::WriterSystem() :
	_addItem(true)
{

}

WriterSystem::~WriterSystem()
{

}

bool WriterSystem::initialize(
	uint_fast8_t id,
	NLE::Core::IEngine& iEngine)
{
	_id = id;

	_master = &iEngine.getMSDistributor<double>(MS_CONTAINER).buildMasterEndpoint(id);
	_shared = &iEngine.getSDistributor<double>(S_CONTAINER).buildEndpoint(id);

	return true;
}

void WriterSystem::release()
{

}

uint_fast8_t WriterSystem::getID()
{
	return _id;
}

std::function<void()> WriterSystem::getExecutionProcedure()
{
	NLE::Core::Data::MasterContainer<double>& master = *_master;
	NLE::Core::Data::SContainer<double>& shared = *_shared;
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