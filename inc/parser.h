#ifndef ABSTRACTVM_PARSER_H
#define ABSTRACTVM_PARSER_H

#include "Error.h"
#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include "../inc/lexer.h"
#include "../inc/IVm.h"
#include "../inc/IOperands.h"
#include <boost/any.hpp>
#include <deque>

typedef ::std::deque<IOperand const *> Container;

class Parser: public IVirtualMachine
{
public:
	Parser();
	~Parser();

	Parser(Parser const & p);
	Parser & operator=(Parser const &p);

	Parser(IVirtualMachine * lexer);

	eOperandType defineType(std::string const &s);

	void execute();

	void op_push(IOperand const * operand);

	void op_pop();

	void op_dump() const;

	void op_assert(std::string const &s);

	void op_add();

	void op_sub();

	void op_mul();

	void op_div();

	void op_mod();

	void op_print();

	void op_exit() const;


private:
	const CreateOperands *_factory_ = nullptr;
	std::vector<std::vector<std::string>> container_;
	std::map<eLexems, std::string> _commands_;

	Container _stack_;

};


#endif //ABSTRACTVM_PARSER_H
