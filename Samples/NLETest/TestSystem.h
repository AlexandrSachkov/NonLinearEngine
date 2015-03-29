#ifndef TEST_SYSTEM_H_
#define TEST_SYSTEM_H_

#include "NLE\NLCore\NL_System.h"
#include <memory>

class SysTask;
class Scheduler;
class SysData;
class TestSystem : public NLE::Core::System
{
public:
	TestSystem();
	~TestSystem();

	bool initialize(uint_fast8_t id);
	void release();

	uint_fast8_t getID();
	NLE::Core::SysTask* getTask(
		std::unique_ptr<NLE::Core::Scheduler> const& scheduler,
		std::unique_ptr<NLE::Core::SysData> const& sysData);

private:
	uint_fast8_t _id;
};

#endif