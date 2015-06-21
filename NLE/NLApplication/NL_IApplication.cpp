#include "NL_IApplication.h"
#include "NL_Application.h"

namespace NLE
{
	IApplication::IApplication(Application& system)
	{
		_system = &system;
	}

	IApplication::~IApplication()
	{

	}

	bool IApplication::initialized()
	{
		return _system->initialized();
	}
}