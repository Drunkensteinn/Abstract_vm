//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#include "../inc/parser.h"
#include <iostream>
#include <string>


Parser::Parser() {
	op_arr_[_push] = "push";
	op_arr_[_pop] = "pop";
	op_arr_[_dump] = "dump";
	op_arr_[_assert] = "assert";
	op_arr_[_add] = "add";
	op_arr_[_sub] = "subb";
	op_arr_[_mult] = "mult";
	op_arr_[_div] = "div";
	op_arr_[_mod] = "mod";
	op_arr_[_print] = "print";
	op_arr_[_exit] = "exit";
}

Parser::~Parser() {}

Parser::Parser(Parser const &p) {
		this->buff_ = p.buff_;
		this->error_manager_ = p.error_manager_;
		this->op_arr_ = p.op_arr_;
}

Parser & Parser::operator=(Parser const &p) {
	if (this != &p)
	{
		this->buff_ = p.buff_;
		this->error_manager_ = p.error_manager_;
	}
	return *this;
}

void Parser::execute() {
	std::getline(std::cin, buff_);// here is an entry point of parsing

	throw Error("fuck");
}


std::string Parser::get_buff() const {
	return this->buff_;
}

void Parser::set_buff(std::string const & buff) {
	this->buff_ = buff;
}

Error const & Parser::get_error_manager() const {
	return (this->error_manager_);
}

void Parser::set_error_manager(Error const & error_operator) {
	this->error_manager_ = error_operator;
}
