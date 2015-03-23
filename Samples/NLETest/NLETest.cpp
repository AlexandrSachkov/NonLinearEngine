#include <iostream>
#include <Windows.h>
#include "NLE\NLCore\NL_DeviceCore.h"
#include "TestSystem.h"

int main(){
	NLE::Core::DeviceCore& devCore = NLE::Core::DeviceCore::instance();
	devCore.initialize();
	for (int i = 0; i < 12; i++)
	{
		devCore.attachSystem(new TestSystem(i));
	}
	printf("Started...\n");
	//while (true)
	//{
		devCore.drive();
		//Sleep(1);
	//}
	printf("ENDED...\n");
	std::cin.ignore();
	return 0;
}