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
#include <sstream>
#include <map>

enum eOperations
{
	begin,
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
	_Int8,
	_Int16,
	_Int32,
	_Float,
	_Double,
	_EOF,
	end,
	count = 12,
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


	void execute();

private:
	std::map<eOperations, std::string> commands;
	std::map<size_t, std::string, std::string, std::string> lexems;//create a vector of vectors
	std::ifstream ifile;
};


#endif //ABSTRACTVM_LEXER_H
