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
	WriterSystem(NLE::Core::Priority priority);
	~WriterSystem();

	bool initialize(
		uint_fast8_t sysId,
		std::unique_ptr<NLE::Core::StateManager> const& stateManager);

	void release();
	NLE::Core::ExecutionDesc getExecutionDesc();
	uint_fast8_t getID();

	std::function<void()> getExecutionProcedure();

private:
	uint_fast8_t _id;
	NLE::Core::Priority _priority;
	bool _addItem;

	NLE::Core::Data::MasterContainer* _master;
	NLE::Core::Data::SContainer* _shared;
};

#endif