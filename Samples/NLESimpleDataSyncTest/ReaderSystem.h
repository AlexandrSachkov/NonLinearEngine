#ifndef READER_SYSTEM_H_
#define READER_SYSTEM_H_

#include "NLE\NLCore\NL_System.h"
#include "NLE\NLCore\NL_SlaveContainer.h"
#include "NLE\NLCore\NL_SContainer.h"
#include <memory>

class SysTask;
class Scheduler;
class StateManager;


class ReaderSystem : public NLE::Core::System
{
public:
	ReaderSystem(uint_fast32_t id);
	~ReaderSystem();

	bool initialize(NLE::Core::IEngine& iEngine);

	void release();
	uint_fast32_t getID();

	std::function<void()> getExecutionProcedure();

private:
	uint_fast32_t _id;

	NLE::Core::Data::SlaveContainer<double>* _slave;
	NLE::Core::Data::SContainer<double>* _shared;
};

#endif