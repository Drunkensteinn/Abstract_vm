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
#include <vector>
#include <algorithm>

enum eLexems
{
	begin,
	_PUSH,
	_POP,
	_DUMP,
	_ASSERT,
	_ADD,
	_SUB,
	_MULT,
	_DIV,
	_MOD,
	_PRINT,
	_EXIT,
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

	void pack_lexems(size_t index, std::string command, std::string operand, std::string value);

	void validate_operand_arg(std::string const &operand, size_t pc);

	std::vector<std::vector<std::string>> const get_lexems() const;

	void execute() final;

private:
	std::map<eLexems, std::string> commands;
	std::vector<std::vector<std::string>> lexems;//create a vector of vectors
	std::ifstream ifile;
};


#endif //ABSTRACTVM_LEXER_H
