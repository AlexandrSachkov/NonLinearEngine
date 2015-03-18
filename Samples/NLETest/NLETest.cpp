#include <iostream>
#include "NLE\NLCore\NL_DeviceCore.h"
#include "TestSystem.h"

int main(){

	NLE::Core::DeviceCore& devCore = NLE::Core::DeviceCore::instance();
	devCore.initialize();
	for (int i = 0; i < 100; i++)
	{
		devCore.attachSystem(new TestSystem(i));
	}
	printf("Started...\n");
	for (int i = 0; i < 2; i++)
	{
		devCore.run();
	}
	printf("ENDED...\n");
	std::cin.ignore();
	return 0;
}