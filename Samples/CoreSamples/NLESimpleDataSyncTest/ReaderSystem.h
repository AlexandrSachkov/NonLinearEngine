#ifndef READER_SYSTEM_H_
#define READER_SYSTEM_H_

#include "NLE\NLCore\NL_System.h"
#include "NLE\NLCore\NL_SlaveContainer.h"
#include "NLE\NLCore\NL_SContainer.h"
#include "NLE\NLCore\NL_ISystem.h"
#include <memory>

class SysTask;
class Scheduler;
class StateManager;
class RSysInterface;

class ReaderSystem : public NLE::Core::System, public NLE::Core::ISystem
{
public:
	ReaderSystem(uint_fast32_t id);
	~ReaderSystem();

	bool initialize(NLE::Core::IEngine& iEngine);
	bool initialized();
	void release();
	uint_fast32_t getID();

	std::function<void()> const& getExecutionProcedure();
	NLE::Core::ISystem& getInterface();

private:
	uint_fast32_t _id;
	bool _initialized;
	std::function<void()> _procedure;

	NLE::Core::Data::SlaveContainer<double>* _slave;
	NLE::Core::Data::SContainer<double>* _shared;
};

#endif