#include <iostream>

#include "NLE\NLCore\NL_DeviceCore.h"
#include "WriterSystem.h"
#include "ReaderSystem.h"
#include "TestStateManager.h"

int main(){
	NLE::Core::DeviceCore& devCore = NLE::Core::DeviceCore::instance();
	devCore.attachStateManager(std::make_unique<TestStateManager>());
	devCore.setClockPeriodNs(1000000000L);

	NLE::Core::ExecutionDesc execDesc
		(
		NLE::Core::Priority::STANDARD,
		NLE::Core::Execution::RECURRING,
		NLE::Core::Startup::AUTOMATIC,
		0
		);

	devCore.attachSystem(execDesc, std::unique_ptr<WriterSystem>(new WriterSystem()));
	devCore.attachSystem(execDesc, std::unique_ptr<ReaderSystem>(new ReaderSystem()));
	devCore.attachSystem(execDesc, std::unique_ptr<ReaderSystem>(new ReaderSystem()));

	devCore.initialize();

	printf("Started...\n");

	devCore.run();
	return 0;
}