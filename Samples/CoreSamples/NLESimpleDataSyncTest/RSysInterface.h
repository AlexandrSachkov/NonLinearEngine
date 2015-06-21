#ifndef SYS_INTERFACE_H_
#define SYS_INTERFACE_H_

#include "NLE\NLCore\NL_ISystem.h"

class ReaderSystem;

class RSysInterface : public NLE::Core::ISystem
{
public:
	RSysInterface(ReaderSystem& system);
	~RSysInterface();

	bool initialized();

private:
	ReaderSystem* _system;
};

#endif