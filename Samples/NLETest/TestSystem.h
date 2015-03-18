#ifndef TEST_SYSTEM_H_
#define TEST_SYSTEM_H_

#include "NLE\NLCore\NL_System.h"

class SysTask;
class TestSystem : public NLE::Core::System
{
public:
	TestSystem(int id);
	~TestSystem();

	int getID();
	NLE::Core::SysTask* getTask();

private:
	int _id;
};

#endif