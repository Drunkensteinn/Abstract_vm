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
	CreateOperands *factory = new CreateOperands;

	try {
		Operand<double> op(std::string("127.1212312312312"), Double, 7, factory);
		Operand<float> op1(std::string("127.12"), Float, 5, factory);
		std::cout << op + op1 << std::endl;}
	catch (Error & e) { std::cout << e.what() << std::endl; }

	IVirtualMachine *lexer = new Lexer(argc, argv);
	execute(lexer);

	IVirtualMachine *parser = new Parser(dynamic_cast<Lexer *>(lexer)->get_lexems());
	execute(parser);
	return (0);
}