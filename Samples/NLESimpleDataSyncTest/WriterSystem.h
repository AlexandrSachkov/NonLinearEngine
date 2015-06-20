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
	WriterSystem(uint_fast32_t id);
	~WriterSystem();

	bool initialize(NLE::Core::IEngine& iEngine);

	void release();
	uint_fast32_t getID();

	std::function<void()> getExecutionProcedure();
	NLE::Core::ISystem* getInterface();

private:
	uint_fast32_t _id;
	bool _addItem;

	NLE::Core::Data::MasterContainer<double>* _master;
	NLE::Core::Data::SContainer<double>* _shared;
};

#endif