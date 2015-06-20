#include "WSysInterface.h"
#include "WriterSystem.h"

WSysInterface::WSysInterface(WriterSystem& system) :
_system(&system)
{
}

WSysInterface::~WSysInterface()
{
}

bool WSysInterface::initialized()
{
	return _system->initialized();
}

