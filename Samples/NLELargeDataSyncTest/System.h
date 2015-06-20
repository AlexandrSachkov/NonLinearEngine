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
	System(uint_fast32_t id);
	~System();

	bool initialize(NLE::Core::IEngine& iEngine);
	void release();

	std::function<void()> getExecutionProcedure();

private:
	uint_fast32_t _id;

	NLE::Core::Data::SContainer<Data>* _shared;
	NLE::Core::IEngine* _iEngine;
	std::function<void()> _operation;
};

#endif