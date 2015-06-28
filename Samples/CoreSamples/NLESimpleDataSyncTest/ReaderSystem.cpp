#include "ReaderSystem.h"
#include "SharedDataId.h"
#include "NLE\NLCore\NL_IEngine.h"
#include "RSysInterface.h"

ReaderSystem::ReaderSystem(uint_fast32_t id) :
_id(id),
_initialized(false)
{
	_interface = new RSysInterface(*this);
}

ReaderSystem::~ReaderSystem()
{

}

bool ReaderSystem::initialize(NLE::Core::IEngine& iEngine)
{
	_slave = &iEngine.getMSDistributor<double>(MS_CONTAINER).buildSlaveEndpoint(_id);
	_shared = &iEngine.getSDistributor<double>(S_CONTAINER).buildEndpoint(_id);

	_procedure = [&](){
		printf("Reader #%i\n", getID());
		printf("SContainer:\n");
		for (unsigned int i = 0; i < _shared->size(); ++i)
		{
			printf("%f\n", (*_shared)[i]);
		}
		printf("\n");

		printf("MSContainer:\n");
		for (unsigned int i = 0; i < _slave->size(); ++i)
		{
			printf("%f\n", (*_slave)[i]);
		}
		printf("\n");
	};
	_initialized = true;
	return true;
}

void ReaderSystem::release()
{
	_initialized = false;
}

bool ReaderSystem::initialized()
{
	return _initialized;
}

uint_fast32_t ReaderSystem::getID()
{
	return _id;
}

std::function<void()> const& ReaderSystem::getExecutionProcedure()
{
	return _procedure;
}

NLE::Core::ISystem& ReaderSystem::getInterface()
{
	return *_interface;
}