//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#include "../inc/parser.h"
#include <iostream>
#include <string>


Parser::Parser() {}

Parser::~Parser() {}

Parser::Parser(std::vector<std::vector<std::string>> const &l): container_(l), _factory_(new CreateOperands) {}

Parser::Parser(Parser const &p) {
    container_ = p.container_;
}

Parser & Parser::operator=(Parser const &p) {
	if (this != &p) {
	    container_ = p.container_;
	}
	return *this;
}


void Parser::execute() {
	if (!this->container_.empty())
	{
		size_t _size_raw_ = container_.size();
		for (size_t i = 0; i < _size_raw_; i++)
		{

		}

	}
	else
		throw Error("Empty operation's stack");
}

