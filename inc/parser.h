//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#ifndef ABSTRACTVM_PARSER_H
#define ABSTRACTVM_PARSER_H

#include "Error.h"
#include <iostream>
#include <vector>
#include <map>
#include "../inc/IVm.h"


class Parser: public IVirtualMachine
{
public:
	Parser();
	~Parser();

	Parser(Parser const & p);
	Parser & operator=(Parser const &p);

	Parser (std::vector<std::vector<std::string>> const &l);

	void execute();



private:
	std::vector<std::vector<std::string>> container_;
};


#endif //ABSTRACTVM_PARSER_H
