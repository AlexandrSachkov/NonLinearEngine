#ifndef TEST_SYSTEM_H_
#define TEST_SYSTEM_H_

#include "NLE\NLCore\NL_System.h"
#include "NLE\NLCore\NL_ISystem.h"
#include <memory>

class SysTask;
class Scheduler;
class StateManager;
class SysInterface;
struct SysInitializer;

class TestSystem : public NLE::Core::System, public NLE::Core::ISystem
{
public:
	TestSystem(uint_fast32_t id);
	~TestSystem();

	bool initialize(NLE::Core::IEngine& iEngine, std::unique_ptr<NLE::Core::SysInitializer> const& initializer);
	bool initialized();
	void release();
	uint_fast32_t getID();

	std::function<void()> const& getExecutionProcedure();
	NLE::Core::ISystem& getInterface();

private:
	uint_fast32_t _id;
	bool _initialized;
	std::function<void()> _procedure;
};

#endif