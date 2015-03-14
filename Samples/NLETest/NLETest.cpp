#include <iostream>
#include "NLE\NLCore\NL_Core.h"

int main(){

	int number = NLE::Core::getNumber();
	printf("My number is: %i", number);
	return 0;
}