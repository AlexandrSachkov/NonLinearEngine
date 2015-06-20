#include "SysInterface.h"
#include "TestSystem.h"

SysInterface::SysInterface(TestSystem& system) :
_system(&system)
{
}

SysInterface::~SysInterface()
{
}

bool SysInterface::initialized()
{
	return _system->initialized();
}

