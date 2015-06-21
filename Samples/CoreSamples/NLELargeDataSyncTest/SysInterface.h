#ifndef SYS_INTERFACE_H_
#define SYS_INTERFACE_H_

#include "NLE\NLCore\NL_ISystem.h"

class TestSystem;

class SysInterface : public NLE::Core::ISystem
{
public:
	SysInterface(TestSystem& system);
	~SysInterface();

	bool initialized();

private:
	TestSystem* _system;
};

#endif