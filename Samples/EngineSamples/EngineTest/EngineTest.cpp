#include <iostream>
#include "NLE\NL_Engine.h"

int main()
{
	NLE::IEngine* engine = NLE::GetNLE();
	if (engine->initialize())
	{
		printf("Engine initialized");
		engine->run();
	}
	
	printf("Engine test running...\n");
	return 0;
}