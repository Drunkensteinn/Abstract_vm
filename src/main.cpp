#include <iostream>
#include "../inc/Error.h"
#include "../inc/parser.h"




int main()
{
	Parser *vm = new Parser;

	try {
		vm->execute();
	}
	catch(Error &e) {
		std::cout <<  e.what() << std::endl;
	}
	return 0;
}