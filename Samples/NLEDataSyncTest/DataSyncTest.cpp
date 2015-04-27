#include <iostream>

#include "NLE\NLCore\NL_DeviceCore.h"
#include "WriterSystem.h"
#include "ReaderSystem.h"
#include "TestStateManager.h"

int main(){
	NLE::Core::DeviceCore& devCore = NLE::Core::DeviceCore::instance();
	devCore.attachStateManager(std::make_unique<TestStateManager>());
	devCore.setClockPeriodNs(1000000000L);

	devCore.attachSystem(std::unique_ptr<WriterSystem>(new WriterSystem(NLE::Core::Priority::STANDARD)));
	devCore.attachSystem(std::unique_ptr<ReaderSystem>(new ReaderSystem(NLE::Core::Priority::STANDARD)));
	devCore.attachSystem(std::unique_ptr<ReaderSystem>(new ReaderSystem(NLE::Core::Priority::STANDARD)));

	devCore.initialize();

	printf("Started...\n");

	devCore.run();
	return 0;
}