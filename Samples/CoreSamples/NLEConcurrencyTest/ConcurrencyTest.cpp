#include <iostream>
#include "NLE\NLCore\NL_DeviceCore.h"
#include "TestSystem.h"
#include "NLE\NLCore\NL_ExecutionDesc.h"

int main(){
	NLE::Core::DeviceCore& devCore = NLE::Core::DeviceCore::instance();

	NLE::Core::ExecutionDesc execDesc
		(
			NLE::Core::Priority::STANDARD,
			NLE::Core::Execution::RECURRING,
			NLE::Core::Mode::ASYNC,
			NLE::Core::Startup::AUTOMATIC,
			0
		);

	for (unsigned int i = 0; i < devCore.getNumThreads(); i++)
	{
		devCore.attachSystem(i, execDesc, std::unique_ptr<TestSystem>(new TestSystem(i)));
	}
	devCore.initialize();

	printf("Started...\n");

	devCore.run();
	return 0;
}