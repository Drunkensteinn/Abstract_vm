#ifndef ABSTRACTVM_PARSER_H
#define ABSTRACTVM_PARSER_H

#include "Error.h"
#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include "../inc/IVm.h"
#include "../inc/IOperands.h"


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
	const CreateOperands *_factory_ = nullptr;
	std::vector<std::vector<std::string>> container_;
};


#endif //ABSTRACTVM_PARSER_H
