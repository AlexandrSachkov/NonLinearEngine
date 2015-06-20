#ifndef SYS_INTERFACE_H_
#define SYS_INTERFACE_H_

#include "NLE\NLCore\NL_ISystem.h"

class WriterSystem;

class WSysInterface : public NLE::Core::ISystem
{
public:
	WSysInterface(WriterSystem& system);
	~WSysInterface();

	bool initialized();

private:
	WriterSystem* _system;
};

#endif