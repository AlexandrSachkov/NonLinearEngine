#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "NLE\NLCore\NL_System.h"
#include "NLE\NLCore\NL_SContainer.h"
#include <memory>
#include "Data.h"

class SysTask;
class Scheduler;
class StateManager;

class TestSystem : public NLE::Core::System
{
public:
	TestSystem(uint_fast32_t id);
	~TestSystem();

	bool initialize(NLE::Core::IEngine& iEngine);
	void release();

	std::function<void()> getExecutionProcedure();
	NLE::Core::ISystem* getInterface();

private:
	uint_fast32_t _id;

	NLE::Core::Data::SContainer<Data>* _shared;
	NLE::Core::Data::SContainer<Data>* _sharedReader;
	NLE::Core::IEngine* _iEngine;
	std::function<void()> _operation;
};

#endif