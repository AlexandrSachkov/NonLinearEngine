#include <iostream>

#include "NLE\NLCore\NL_DeviceCore.h"
#include "System.h"
#include "Data.h"

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

	for (unsigned int i = 0; i < devCore.getNumHardwareThreads(); ++i)
	{
		devCore.installSContainer<Data>(i, 10);
		devCore.attachSystem(execDesc, std::unique_ptr<System>(new System()));
	}	
	devCore.initialize();

	printf("Started...\n");

	devCore.run();
	return 0;
}