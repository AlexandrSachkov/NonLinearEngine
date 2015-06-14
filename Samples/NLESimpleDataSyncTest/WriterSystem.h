#ifndef WRITER_SYSTEM_H_
#define WRITER_SYSTEM_H_

#include "NLE\NLCore\NL_System.h"
#include "NLE\NLCore\NL_MasterContainer.h"
#include "NLE\NLCore\NL_SContainer.h"
#include <memory>

class SysTask;
class Scheduler;
class StateManager;

class WriterSystem : public NLE::Core::System
{
public:
	WriterSystem();
	~WriterSystem();

	bool initialize(
		uint_fast8_t sysId,
		NLE::Core::StateManager* stateManager,
		NLE::Core::SysRuntimeControl& sysRuntimeControl);

	void release();
	uint_fast8_t getID();

	std::function<void()> getExecutionProcedure();

private:
	uint_fast8_t _id;
	bool _addItem;

	NLE::Core::Data::MasterContainer<double>* _master;
	NLE::Core::Data::SContainer<double>* _shared;
};

#endif