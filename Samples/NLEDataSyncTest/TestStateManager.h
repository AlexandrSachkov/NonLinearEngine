#ifndef TEST_STATE_MANAGER_H_
#define TEST_STATE_MANAGER_H_

#include <cstdio>
#include "NLE\NLCore\NL_StateManager.h"
#include "NLE\NLCore\NL_SDistributor.h"
#include "NLE\NLCore\NL_MSDistributor.h"

class TestStateManager : public NLE::Core::StateManager
{
public:
	TestStateManager() :
		msDistributor(5),
		sDistributor(5, 5)
	{

	}

	~TestStateManager()
	{

	}

	bool initialize()
	{
		return true;
	}

	void release()
	{

	}

	void processRequests()
	{
		msDistributor.processRequests();
	}

	void distributeFrom(uint_fast8_t sysId)
	{
		msDistributor.distributeFrom(sysId);
		sDistributor.distributeFrom(sysId);
	}

	void distributeTo(uint_fast8_t sysId)
	{
		msDistributor.distributeTo(sysId);
		sDistributor.distributeTo(sysId);
	}

	NLE::Core::Data::MSDistributor msDistributor;
	NLE::Core::Data::SDistributor sDistributor;
private:
};

#endif