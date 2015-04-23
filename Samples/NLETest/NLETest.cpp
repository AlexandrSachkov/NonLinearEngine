#include <iostream>
//#include <Windows.h>
#include "NLE\NLCore\NL_DeviceCore.h"
#include "TestSystem.h"
#include "TestStateManager.h"

int main(){
	NLE::Core::DeviceCore& devCore = NLE::Core::DeviceCore::instance();
	devCore.attachStateManager(std::make_unique<TestStateManager>());
	devCore.setClockFrequencyNs(1000000000L);

	for (int i = 0; i < 12; i++)
	{
		devCore.attachSystem(std::unique_ptr<TestSystem>(new TestSystem(NLE::Core::ExecutionType::ASYNC, NLE::Core::Priority::STANDARD)));
	}
	devCore.initialize();

	printf("Started...\n");

	devCore.run();
	return 0;
}