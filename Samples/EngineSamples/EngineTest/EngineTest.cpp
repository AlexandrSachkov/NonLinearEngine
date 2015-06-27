#include <iostream>
#include "NLE\Engine\NL_Nle.h"

int main()
{
	NLE::INle* engine = NLE::GetNLE();
	if (engine->initialize())
	{
		printf("Engine initialized");
		engine->run();
	}
	
	printf("Engine test running...\n");
	return 0;
}