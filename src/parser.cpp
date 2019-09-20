//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#include "../inc/parser.h"
#include <iostream>
#include <string>


Parser::Parser() {
}

Parser::~Parser() {}

Parser::Parser(Parser const &p) {
		this->buff_ = p.buff_;
		this->error_manager_ = p.error_manager_;
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
//	std::getline(std::cin, buff_);// here is an entry point of parsing

//	throw Error("fuck");
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
