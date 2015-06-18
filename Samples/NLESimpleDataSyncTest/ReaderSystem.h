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
	ReaderSystem();
	~ReaderSystem();

	bool initialize(
		uint_fast8_t sysId,
		NLE::Core::IEngine& iEngine);

	void release();
	uint_fast8_t getID();

	std::function<void()> getExecutionProcedure();

private:
	uint_fast8_t _id;

	NLE::Core::Data::SlaveContainer<double>* _slave;
	NLE::Core::Data::SContainer<double>* _shared;
};

#endif