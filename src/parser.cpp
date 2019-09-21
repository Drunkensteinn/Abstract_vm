//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#include "../inc/parser.h"
#include <iostream>
#include <string>


Parser::Parser() {}

Parser::~Parser() {}

Parser::Parser(std::vector<std::vector<std::string>> const &l): container_(l) {}

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

}

