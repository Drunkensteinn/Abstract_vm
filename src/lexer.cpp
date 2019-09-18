//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#include <sstream>
#include "../inc/lexer.h"


Lexer::Lexer() {}

Lexer::~Lexer() {}

Lexer::Lexer(Lexer const &l) {
}

Lexer& Lexer::operator=(Lexer const &l) {
	if (this != &l) {
	}
	return *this;
}

Lexer::Lexer(int argc, char **argv) {
	if (argc == 2)
	{
		ifile.open(argv[1], std::fstream::out | std::fstream::in);
		if (!ifile)
			throw Error(BAD_FILE);
	}
	else if (argc > 2)
		throw Error(INVALID_NUMBER_OF_ARGS);
}

void Lexer::define_commands() {
	commands[_push] = "push";
	commands[_pop] = "pop";
	commands[_dump] = "dump";
	commands[_assert] = "assert";
	commands[_add] = "add";
	commands[_sub] = "subb";
	commands[_mult] = "mult";
	commands[_div] = "div";
	commands[_mod] = "mod";
	commands[_print] = "print";
	commands[_exit] = "exit";
	commands[_EOF] = "";
}

void Lexer::define_operands() {
	operands[Int8] = "Int8";
	operands[Int16] = "Int16";
	operands[Int32] = "Int32";
	operands[Float] = "Float";
	operands[Double] = "Double";
}

void Lexer::execute() {
	define_operands();
	define_commands();
	std::string line;
	while (std::getline((ifile.is_open() ? (ifile) : (std::cin)), line))
	{
//		size_t operand_iter = Int8;
//		size_t operations_iter = _push;
		std::istringstream  StringStream(line);
		std::string operation;
		std::string operand;
		bool compared = false;
		if (!(StringStream >> operation >> operand))
			break ;
		for (size_t operation_iter = _push; operation_iter != _EOF; operation_iter++)
		{
			std::cout << commands. << std::endl;
//			if (commands)
				compared = true;
		}
	}
}