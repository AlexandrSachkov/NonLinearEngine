#ifndef TEST_SYSTEM_H_
#define TEST_SYSTEM_H_

#include "NLE\NLCore\NL_System.h"

class SysTask;
class TestSystem : public NLE::Core::System
{
public:
	TestSystem(uint_fast8_t id);
	~TestSystem();

	uint_fast8_t getID();
	NLE::Core::SysTask* getTask();

private:
	uint_fast8_t _id;
};

#endif