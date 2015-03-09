#include <iostream>
#include "NLE\NLCore\NLCore.h"

int main(){

	int number = NLE::Core::getNumber();
	printf("My number is: %i", number);
	return 0;
}