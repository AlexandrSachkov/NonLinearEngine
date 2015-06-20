#include "RSysInterface.h"
#include "ReaderSystem.h"

RSysInterface::RSysInterface(ReaderSystem& system) :
_system(&system)
{
}

RSysInterface::~RSysInterface()
{
}

bool RSysInterface::initialized()
{
	return _system->initialized();
}

