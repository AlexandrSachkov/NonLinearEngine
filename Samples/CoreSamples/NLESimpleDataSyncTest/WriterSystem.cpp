#include "WriterSystem.h"
#include "SharedDataId.h"
#include "NLE\NLCore\NL_IEngine.h"
#include "NLE\NLCore\NL_MSDistributor.h"
#include "NLE\NLCore\NL_SDistributor.h"

WriterSystem::WriterSystem(uint_fast32_t id) :
	_addItem(true),
	_id(id),
	_initialized(false)
{

}

WriterSystem::~WriterSystem()
{

}

bool WriterSystem::initialize(NLE::Core::IEngine& iEngine)
{
	_master = &static_cast<NLE::Core::Data::MSDistributor<double>*>(&iEngine.getMSDistributor(MS_CONTAINER))->buildMasterEndpoint(_id);
	_shared = &static_cast<NLE::Core::Data::SDistributor<double>*>(&iEngine.getSDistributor(S_CONTAINER))->buildEndpoint(_id);

	_procedure = [&](){
		for (unsigned int i = 0; i < _shared->size(); ++i)
		{
			_shared->modify(i, (*_shared)[i] + 1);
		}

		if (_addItem)
		{
			_master->add(10);
			if (_master->size() == 10)
			{
				_addItem = false;
			}
		}
		else
		{
			_master->remove(0);
			if (_master->size() == 0)
			{
				_addItem = true;
			}
		}

		for (unsigned int i = 0; i < _master->size(); i++)
		{
			_master->modify(i, (*_master)[i] + 1);
		}
	};

	_initialized = true;
	return true;
}

void WriterSystem::release()
{
	_initialized = false;
}

bool WriterSystem::initialized()
{
	return _initialized;
}

uint_fast32_t WriterSystem::getID()
{
	return _id;
}

std::function<void()> const& WriterSystem::getExecutionProcedure()
{
	return _procedure;
}

NLE::Core::ISystem& WriterSystem::getInterface()
{
	return *this;
}