#include <iostream>
#include "NLE\NLCore\NL_DeviceCore.h"
#include "TestSystem.h"

int main(){
	NLE::Core::DeviceCore& devCore = NLE::Core::DeviceCore::instance();
	devCore.setClockPeriodNs(1000000000L);

	NLE::Core::ExecutionDesc execDesc
		(
			NLE::Core::Priority::STANDARD,
			NLE::Core::Execution::RECURRING,
			NLE::Core::Startup::AUTOMATIC,
			0
		);

	for (int i = 0; i < devCore.getNumHardwareThreads(); i++)
	{
		devCore.attachSystem(execDesc, std::unique_ptr<TestSystem>(new TestSystem()));
	}
	devCore.initialize();

	printf("Started...\n");

	devCore.run();
	return 0;
}