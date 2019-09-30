//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#include "../inc/parser.h"
#include "../inc/lexer.h"
#include <iostream>
#include <string>

#define COMMAND 0
#define OPERAND 1
#define VALUE 2


Parser::Parser() {}

Parser::~Parser() {}

Parser::Parser(IVirtualMachine * lexer): _factory_(new CreateOperands) {
	this->container_ = dynamic_cast<Lexer *>(lexer)->get_lexems();
	this->_commands_ = dynamic_cast<Lexer *>(lexer)->get_commands();
}

Parser::Parser(Parser const &p) {
    container_ = p.container_;
}

Parser & Parser::operator=(Parser const &p) {
	if (this != &p) {
	    container_ = p.container_;
	}
	return *this;
}

eOperandType Parser::defineType(std::string const &s)
{
	if (s == this->_commands_[_Int8])
		return Int8;
	else if (s == this->_commands_[_Int16])
		return Int16;
	else if (s == this->_commands_[_Int32])
		return Int32;
	else if (s == this->_commands_[_Float])
		return Float;
	else if (s == this->_commands_[_Double])
		return Double;
	else
		throw Error("Error: Invalid Operand type");
}

void Parser::op_exit() const {
	::exit(0);
}

void Parser::op_push(IOperand const * operand) {
	this->_stack_.push_front(operand);
}

void Parser::op_pop() {
	if (not this->_stack_.empty()) {
		this->_stack_.pop_front();
	}
	else
		throw Error("Pop on empty stack");
}

void Parser::op_dump() const {
	for (size_t i = 0; i < this->_stack_.size(); i++) {
		std::cout << this->_stack_.at(i)->toString() << std::endl;
	}
}


void Parser::op_assert(std::string const &s) {
	long double l1;
	long double l2;

	l1 = boost::lexical_cast<long double>(s);
	l2 = boost::lexical_cast<long double>(this->_stack_.at(0));

	if (l1 != l2)
		throw Error("Error: assert failed");
}

void Parser::op_add() {
	IOperand const *p1;
	IOperand const *p2;
	IOperand const *res;

	if (this->_stack_.size() >= 2) {
		p1 = this->_stack_.front();
		this->_stack_.pop_front();
		p2 = this->_stack_.front();
		this->_stack_.pop_front();
		res = *p1 + *p2;
		this->_stack_.push_front(res);
	}
	else
		throw Error("Add instruction on empty stack");
}


void Parser::op_sub() {
	IOperand const *p1;
	IOperand const *p2;
	IOperand const *res;

	if (this->_stack_.size() >= 2) {
		p1 = this->_stack_.front();
		this->_stack_.pop_front();
		p2 = this->_stack_.front();
		this->_stack_.pop_front();
		res = *p1 - *p2;
		this->_stack_.push_front(res);
	}
	else
		throw Error("Sub instruction on empty stack");
}

void Parser::op_mul() {
	IOperand const *p1;
	IOperand const *p2;
	IOperand const *res;

	if (this->_stack_.size() >= 2) {
		p1 = this->_stack_.front();
		this->_stack_.pop_front();
		p2 = this->_stack_.front();
		this->_stack_.pop_front();
		res = *p1 * *p2;
		this->_stack_.push_front(res);
	}
	else
		throw Error("Mul instruction on empty stack");
}

void Parser::op_div() {
	IOperand const *p1;
	IOperand const *p2;
	IOperand const *res;

	if (this->_stack_.size() >= 2) {
		p1 = this->_stack_.front();
		this->_stack_.pop_front();
		p2 = this->_stack_.front();
		this->_stack_.pop_front();
		res = *p1 / *p2;
		this->_stack_.push_front(res);
	}
	else
		throw Error("Div instruction on empty stack");
}

void Parser::op_mod() {
	IOperand const *p1;
	IOperand const *p2;
	IOperand const *res;

	if (this->_stack_.size() >= 2) {
		p1 = this->_stack_.front();
		this->_stack_.pop_front();
		p2 = this->_stack_.front();
		this->_stack_.pop_front();
		res = *p1 % *p2;
		this->_stack_.push_front(res);
	}
	else
		throw Error("Div instruction on empty stack");
}

void Parser::op_print() {
	if (not this->_stack_.empty()) {
		if (this->_stack_.at(0)->getType() == Int8) {
			std::cout << static_cast<char>(std::stoi(this->_stack_.at(0)->toString())) << std::endl;
		}
	}
	else
		throw  Error("Print on empty stack");
}

void Parser::execute() {
	if (!this->container_.empty())
	{
		size_t _size_raw_ = container_.size();
		for (size_t i = 0; i < _size_raw_; i++)
		{
			if (this->container_.at(i)[COMMAND] == _commands_[_PUSH]) {
				op_push(_factory_->createOperand(defineType(this->container_.at(i)[OPERAND]),
						this->container_.at(i)[VALUE]));
			}
			else if (this->container_.at(i)[COMMAND] == _commands_[_POP]) {
				op_pop();
			}
			else if (this->container_.at(i)[COMMAND] == _commands_[_DUMP]) {
				op_dump();
			}
			else if (this->container_.at(i)[COMMAND] == _commands_[_ASSERT]) {
				op_assert(this->container_.at(i)[VALUE]);
			}
			else if (this->container_.at(i)[COMMAND] == _commands_[_ADD]) {
				op_add();
			}
			else if (this->container_.at(i)[COMMAND] == _commands_[_SUB]) {
				op_sub();
			}
			else if (this->container_.at(i)[COMMAND] == _commands_[_MULT]) {
				op_mul();
			}
			else if (this->container_.at(i)[COMMAND] == _commands_[_DIV]) {
				op_div();
			}
			else if (this->container_.at(i)[COMMAND] == _commands_[_MOD]) {
				op_mod();
			}
			else if (this->container_.at(i)[COMMAND] == _commands_[_PRINT]) {
				op_print();
			}
			else if (this->container_.at(i)[COMMAND] == _commands_[_EXIT]) {
				op_exit();
			}
		}
	}
	else
		throw Error("Empty operation's stack");
}
