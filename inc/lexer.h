/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:58:46 by ablizniu          #+#    #+#             */
/*   Updated: 2019/10/05 16:24:36 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

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

enum eOpIt
{
	_Int8,
	_Int16,
	_Int32,
	_Float,
	_Double,
	_end
};

enum eLexems
{
	_PUSH,
	_POP,
	_DUMP,
	_ASSERT,
	_ADD,
	_SUB,
	_MUL,
	_DIV,
	_MOD,
	_PRINT,
	_EXIT,
	_EOF,
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

	const std::map<eLexems, std::string> get_commands(void) const;

	const std::map<eOpIt, std::string> get_operands(void) const;

	void pack_lexems(size_t index, std::string command, std::string operand, std::string value);

	std::string validate_operand_arg(const std::string operand, size_t pc, bool &operand_compared, std::string &__v__);

	std::vector<std::vector<std::string>> const get_lexems() const;

	void execute() final;

private:
	std::map<eLexems, std::string> commands;
	std::map<eOpIt, std::string> operands;
	std::vector<std::vector<std::string>> lexems;//create a vector of vectors
	std::ifstream ifile;
};


#endif //ABSTRACTVM_LEXER_H
