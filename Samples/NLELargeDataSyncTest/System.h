#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "NLE\NLCore\NL_System.h"
#include "NLE\NLCore\NL_SContainer.h"
#include <memory>
#include "Data.h"

class SysTask;
class Scheduler;
class StateManager;

class System : public NLE::Core::System
{
public:
	System();
	~System();

	bool initialize(
		uint_fast8_t sysId,
		NLE::Core::StateManager* stateManager,
		NLE::Core::SysRuntimeControl& sysRuntimeControl);

	void release();
	uint_fast8_t getID();

	std::function<void()> getExecutionProcedure();

private:
	uint_fast8_t _id;

	NLE::Core::Data::SContainer<Data>* _shared;
	NLE::Core::SysRuntimeControl* _sysRuntimeControl;
};

#endif