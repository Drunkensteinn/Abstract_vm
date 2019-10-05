/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:58:39 by ablizniu          #+#    #+#             */
/*   Updated: 2019/10/05 16:36:05 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../inc/lexer.h"

Lexer::Lexer() {}

Lexer::~Lexer() {}

Lexer::Lexer(Lexer const &l) {
    commands = l.commands;
    lexems = l.lexems;
}

Lexer& Lexer::operator=(Lexer const &l) {
	if (this != &l) {
        commands = l.commands;
        lexems = l.lexems;
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
	commands[_PUSH] = "push";
	commands[_POP] = "pop";
	commands[_DUMP] = "dump";
	commands[_ASSERT] = "assert";
	commands[_ADD] = "add";
	commands[_SUB] = "sub";
	commands[_MUL] = "mul";
	commands[_DIV] = "div";
	commands[_MOD] = "mod";
	commands[_PRINT] = "print";
	commands[_EXIT] = "exit";
	operands[_Int8] = "int8";
	operands[_Int16] = "int16";
	operands[_Int32] = "int32";
	operands[_Float] = "float";
	operands[_Double] = "double";
}

std::vector<std::vector<std::string>> const Lexer::get_lexems() const {
    return this->lexems;
}

const std::map<eLexems, std::string> Lexer::get_commands(void) const {
	return (this->commands);
}

const std::map<eOpIt, std::string> Lexer::get_operands(void) const {
	return this->operands;
}

void Lexer::pack_lexems(size_t index, std::string command, std::string operand, std::string value) {
    this->lexems.resize(index + 1);
    this->lexems.at(index).push_back(command);
    this->lexems.at(index).push_back(operand);
    this->lexems.at(index).push_back(value);
    if (value.find(";") != std::string::npos)
    	throw Error("\nSyntax error: value " + value + " has invalid format");
}

std::string
Lexer::validate_operand_arg(const std::string operand, size_t pc, bool &operand_compared, std::string &__v__) {
    size_t n1;
    size_t n2;
    std::string s;

    n1 = std::count(operand.begin(), operand.end(), ')');
    n2 = std::count(operand.begin(), operand.end(), '(');

	if (n2 or n1) {
		if (((n2 >= 1 and !n1) or (n1 >= 1 and !n2)) or (n2 > 1 or n1 > 1))
			throw Error(std::string("\nSyntax error: Line: " + std::to_string(pc) +
			": Operand ") + operand + std::string(" has invalid argument format"));
	}

    for (size_t _iter = eOpIt::_Int8; _iter != eOpIt::_end; _iter++) {
		eOpIt it = static_cast<eOpIt>(_iter);
		if (operand.find(operands.at(it)) != std::string::npos) {
			s = operands.at(it);
			__v__ = operand.substr(operand.find("(") + 1, operand.find(")") - operand.find("(") - 1);
			operand_compared = true;
		}
	}
    return (s);
}

void Lexer::execute() {
	define_commands();
	std::string line;
    size_t pc = 1;
	while (std::getline((ifile.is_open() ? (ifile) : (std::cin)), line)) {
		std::istringstream StringStream(line.substr(0, line.find(";")));
		std::string operation;
		std::string operand;
		std::string value;
		std::string to_pack_operations;
		std::string to_pack_operand;
		bool compared_operation = false;
		bool compared_operand = false;

		StringStream >> operation >> operand;

		if (line == ";;")
			break ;
		else if (not operation.empty() or not operand.empty()) {
			for (size_t _iter = eLexems::_PUSH; _iter != eLexems::_EOF; _iter++) {
				eLexems it;

				it = static_cast<eLexems>(_iter);
				if (operation.find(commands.at(it)) != std::string::npos) {
					if (commands.at(it) == "push" or commands.at(it) == "assert") {
						to_pack_operand = validate_operand_arg(operand, pc, compared_operand, value);
						to_pack_operations = commands.at(it);
						compared_operation = true;

					} else {
						to_pack_operations = commands.at(it);
						compared_operation = true;
						compared_operand = true;
					}
				}
			}
            if (not compared_operation)
                throw Error(std::string("\nSyntax error: Line: ") + std::to_string(pc) +
                            std::string(": unknown instruction: ") + operation);
            else if (not compared_operand)
                throw Error(std::string("\nSyntax error: Line: ") + std::to_string(pc) + std::string(": unknown operand type: ") + operand.substr(0, operand.find("(")));
            else
                pack_lexems(pc - 1, to_pack_operations, to_pack_operand, value);
			pc++;
        }
	}
}

