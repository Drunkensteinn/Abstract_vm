/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:58:09 by ablizniu          #+#    #+#             */
/*   Updated: 2019/10/04 14:47:07 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	this->_operands_ = dynamic_cast<Lexer *>(lexer)->get_operands();
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

bool Parser::findExitInstruction() {
	size_t _size_ = this->container_.size();
	for (size_t i = 0; i < _size_; i++) {
		if (this->container_.at(i)[COMMAND] == "exit")
			return true;
	}
	return false;
}

eOperandType Parser::defineType(std::string const &s)
{
	if (s == this->_operands_[_Int8])
		return Int8;
	else if (s == this->_operands_[_Int16])
		return Int16;
	else if (s == this->_operands_[_Int32])
		return Int32;
	else if (s == this->_operands_[_Float])
		return Float;
	else if (s == this->_operands_[_Double])
		return Double;
	else
		throw Error(INVALID_OPERADN);
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
		throw Error(POP_EMPTY);
}

void Parser::op_dump() const {
	for (size_t i = 0; i < this->_stack_.size(); i++) {
		std::cout << std::setprecision(this->_stack_.at(i)->getPrecision()) << this->_stack_.at(i)->toString() << std::endl;
	}
}

void Parser::op_assert(std::string const &s) {
	long double l1;
	long double l2;

	l1 = boost::lexical_cast<long double>(s);
	l2 = boost::lexical_cast<long double>(this->_stack_.at(0)->toString());

	if (l1 != l2)
		throw Error(ASSERT_FAILED);
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
		delete(p1);
		delete(p2);
	}
	else
		throw Error(ADD_EMPTY);
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
		delete(p1);
		delete(p2);
	}
	else
		throw Error(SUB_EMPTY);
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
		delete(p1);
		delete(p2);
	}
	else
		throw Error(MUL_EMPTY);
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
		delete(p1);
		delete(p2);
	}
	else
		throw Error(DIV_EMPTY);
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
		delete(p1);
		delete(p2);
	}
	else
		throw Error(MOD_EMPTY);
}

void Parser::op_print() {
	if (not this->_stack_.empty()) {
		if (this->_stack_.at(0)->getType() == Int8) {
			std::cout << static_cast<char>(std::stoi(this->_stack_.at(0)->toString())) << std::endl;
		}
		else
			throw Error(PRINT_ERROR);
	}
	else
		throw  Error(PRINT_EMPTY);
}

void Parser::execute() {
	if (!this->container_.empty())
	{
		size_t _size_raw_ = container_.size();
		if (not findExitInstruction())
			throw Error(NO_EXIT);
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
			else if (this->container_.at(i)[COMMAND] == _commands_[_MUL]) {
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
		throw Error(NO_ELEMS_CONTAINER);
}

