//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#ifndef ABSTRACTVM_LEXER_H
#define ABSTRACTVM_LEXER_H

#include <iostream>
#include "IOperands.h"
#include "IVm.h"
#include "Error.h"
#include "Error_messages.h"
#include <string>
#include <fstream>
#include <map>

enum eOperations
{
	_push,
	_pop,
	_dump,
	_assert,
	_add,
	_sub,
	_mult,
	_div,
	_mod,
	_print,
	_exit,
	_EOF
};

class Lexer: public IVirtualMachine
{
public:

	Lexer();
	~Lexer();

	Lexer(Lexer const &l);
	Lexer &operator=(Lexer const &l);

	Lexer(int argc, char **argv);

	void define_commands();
	void define_operands();
	void execute();

private:
	std::map<eOperations, std::string> commands;
	std::map<eOperandType , std::string> operands;
	std::ifstream ifile;
};


#endif //ABSTRACTVM_LEXER_H
