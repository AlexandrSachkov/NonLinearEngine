#include <iostream>
#include "NLE\NLCore\NL_DeviceCore.h"
#include "TestSystem.h"

int main(){

	NLE::Core::DeviceCore& devCore = NLE::Core::DeviceCore::instance();
	devCore.initialize();
	devCore.attachSystem(new (tbb::task::allocate_root())TestSystem(1));
	devCore.attachSystem(new (tbb::task::allocate_root())TestSystem(2));
	for (int i = 0; i < 2; i++)
	{
		devCore.run();
	}
	std::cout << "Hello, World\n";
	std::cin.ignore();
	return 0;
}