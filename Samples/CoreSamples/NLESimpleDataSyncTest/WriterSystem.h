#ifndef WRITER_SYSTEM_H_
#define WRITER_SYSTEM_H_

#include "NLE\NLCore\NL_System.h"
#include "NLE\NLCore\NL_MasterContainer.h"
#include "NLE\NLCore\NL_SContainer.h"
#include "NLE\NLCore\NL_ISystem.h"
#include <memory>

class SysTask;
class Scheduler;
class StateManager;
class WSysInterface;

class WriterSystem : public NLE::Core::System, public NLE::Core::ISystem
{
public:
	WriterSystem(uint_fast32_t id);
	~WriterSystem();

	bool initialize(NLE::Core::IEngine& iEngine);
	bool initialized();
	void release();
	uint_fast32_t getID();

	std::function<void()> const& getExecutionProcedure();
	NLE::Core::ISystem& getInterface();

private:
	uint_fast32_t _id;
	bool _addItem;
	bool _initialized;
	std::function<void()> _procedure;

	NLE::Core::Data::MasterContainer<double>* _master;
	NLE::Core::Data::SContainer<double>* _shared;
};

#endif