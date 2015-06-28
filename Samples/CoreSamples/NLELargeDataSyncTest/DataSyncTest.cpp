#include <iostream>

#include "NLE\NLCore\NL_DeviceCore.h"
#include "TestSystem.h"
#include "Data.h"
#include "NLE\NLCore\NL_ExecutionDesc.h"

int main(){
	NLE::Core::DeviceCore& devCore = NLE::Core::DeviceCore::instance();
	devCore.setClockPeriodNs(1000000L);

	NLE::Core::ExecutionDesc execDesc
		(
		NLE::Core::Priority::STANDARD,
		NLE::Core::Execution::RECURRING,
		NLE::Core::Mode::ASYNC,
		NLE::Core::Startup::AUTOMATIC,
		0
		);

	printf("Data size: %i", sizeof(Data));
	for (unsigned int i = 0; i < devCore.getNumHardwareThreads(); ++i)
	{
		devCore.installSContainer<Data>(i, 25000, 65);
		devCore.attachSystem(i, execDesc, std::unique_ptr<TestSystem>(new TestSystem(i)));
	}
	devCore.initialize();

	printf("Started...\n");

	devCore.run();
	return 0;
}