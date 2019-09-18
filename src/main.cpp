#include <iostream>
#include "../inc/Error.h"
#include "../inc/parser.h"
#include "../inc/lexer.h"

int main(int argc, char **argv)
{
	IVirtualMachine *lexer = new Lexer(argc, argv);

	try {
		lexer->execute();
	}
	catch(Error &e) {
		std::cout <<  e.what() << std::endl;
	}

	IVirtualMachine *parser = new Parser; // here must a be a transmission of parsed vector

	try {
		parser->execute();
	}
	catch(Error &e) {
		std::cout <<  e.what() << std::endl;
	}
	return (0);
}