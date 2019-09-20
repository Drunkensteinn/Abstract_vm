//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

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
	commands[begin] = "";
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
	commands[_Int8] = "int8";
	commands[_Int16] = "int16";
	commands[_Int32] = "int32";
	commands[_Float] = "float";
	commands[_Double] = "double";
	commands[_EOF] = "";
	commands[end] = "\0";
}

void Lexer::pack_lexems(size_t index, std::string command, std::string operand, std::string value) {
    this->lexems.resize(index + 1);
    this->lexems.at(index).push_back(command);
    this->lexems.at(index).push_back(operand);
    this->lexems.at(index).push_back(value);
}

void Lexer::validate_operand_arg(std::string const &operand, size_t pc) {
    size_t n1;
    size_t n2;

    n1 = std::count(operand.begin(), operand.end(), ')');
    n2 = std::count(operand.begin(), operand.end(), '(');

    if (n1 > 1 or n2 > 1)
        throw Error(std::string("Syntax error: Line: " + std::to_string(pc) + ": Operand ") +
        operand + std::string(" has invalid argument format"));
}

void Lexer::execute() {
	define_commands();
	std::string line;
	while (std::getline((ifile.is_open() ? (ifile) : (std::cin)), line))
	{
		size_t pc = 1;
		std::istringstream  StringStream(line);
		std::string operation;
		std::string operand;
		bool compared_operation = false;
		bool compared_operand = false;

        StringStream >> operation >> operand;
		if (operation == ";;") {
            break ;
        }
		else {
            if (operation.find(";") != std::string::npos)
                continue;

            for (size_t _iter = eOperations::begin; _iter != eOperations::end; _iter++) {
                eOperations it;

                it = static_cast<eOperations>(_iter);
                if (commands.at(it) == operation)
                    compared_operation = true;
                if (commands.at(it) == operand.substr(0, operand.find("(")))
                {
                    validate_operand_arg(operand, pc);
                    compared_operand = true;
                }
            }
            if (not compared_operation)
                throw Error(std::string("Syntax error: Line: ") + std::to_string(pc) +
                            std::string(": unknown instruction: ") + operation);
            else if (not compared_operand)
                throw Error(std::string("Syntax error: Line: ") + std::to_string(pc) +
                            std::string(": unknown operand type: ") + operand.substr(0, operand.find("(")));
            else
                pack_lexems(pc - 1, operation, operand.substr(0, operand.find("(")),
                            operand.substr(operand.find("(") + 1, operand.find(")") - operand.find("(") - 1));
        }
	}
}