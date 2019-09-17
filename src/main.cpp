#include <iostream>
#include "../inc/Error.h"
#include "../inc/parser.h"




int main(int argc, char **argv)
{
	Parser *vm = new Parser;

	try {
		vm->execute();
	}
	catch(Error &e) {
		std::cout <<  e.what() << std::endl;
	}
	__attribute__((noreturn));
}