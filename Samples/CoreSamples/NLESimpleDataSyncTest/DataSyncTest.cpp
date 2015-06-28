#include <iostream>

#include "NLE\NLCore\NL_DeviceCore.h"
#include "WriterSystem.h"
#include "ReaderSystem.h"
#include "SharedDataId.h"
#include "NLE\NLCore\NL_ExecutionDesc.h"

int main(){
	NLE::Core::DeviceCore& devCore = NLE::Core::DeviceCore::instance();
	devCore.setClockPeriodNs(1000000000L);

	NLE::Core::ExecutionDesc execDesc
		(
		NLE::Core::Priority::STANDARD,
		NLE::Core::Execution::RECURRING,
		NLE::Core::Mode::ASYNC,
		NLE::Core::Startup::AUTOMATIC,
		0
		);

	devCore.installMSContainer<double>(MS_CONTAINER, 10, 6500);
	devCore.installSContainer<double>(S_CONTAINER, 10, 6500);

	devCore.attachSystem(0, execDesc, std::unique_ptr<WriterSystem>(new WriterSystem(0)));
	devCore.attachSystem(1, execDesc, std::unique_ptr<ReaderSystem>(new ReaderSystem(1)));
	devCore.attachSystem(2, execDesc, std::unique_ptr<ReaderSystem>(new ReaderSystem(2)));
	
	devCore.initialize();

	printf("Started...\n");

	devCore.run();
	return 0;
}