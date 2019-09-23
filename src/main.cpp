#include <iostream>
#include <bootstrap.h>
#include <boost/lexical_cast.hpp>
#include "../inc/Error.h"
#include "../inc/parser.h"
#include "../inc/lexer.h"


void execute(IVirtualMachine *m)
{
	try { m->execute(); }
	catch (Error &e) {
		std::cout <<  e.what() << std::endl;
		exit(0);
	}
}

int main(int argc, char **argv)
{


	try {
		Operand<int8_t> op(std::string("255"), Int8, 0);
		std::cout << op << std::endl;}
	catch (Error & e) { std::cout << e.what() << std::endl;}

	IVirtualMachine *lexer = new Lexer(argc, argv);
	execute(lexer);

	IVirtualMachine *parser = new Parser(dynamic_cast<Lexer *>(lexer)->get_lexems());
	execute(parser);
	return (0);
}