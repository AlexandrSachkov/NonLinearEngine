#include <iostream>
//#include <Windows.h>
#include "NLE\NLCore\NL_DeviceCore.h"
#include "TestSystem.h"

int main(){
	NLE::Core::DeviceCore& devCore = NLE::Core::DeviceCore::instance();

	for (int i = 0; i < 12; i++)
	{
		devCore.attachSystem(std::make_unique<TestSystem>());
	}
	devCore.initialize();

	printf("Started...\n");
	//while (true)
	//{
		devCore.drive();
	//	Sleep(1);
	//}
	std::cin.ignore();
	return 0;
}