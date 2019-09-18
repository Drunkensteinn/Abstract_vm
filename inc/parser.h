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

	void execute();

	std::string get_buff() const;
	void		set_buff(std::string const & buff);

	Error const &get_error_manager() const;
	void		set_error_manager(Error const & error_operator);


private:
	std::string buff_;
	std::vector<std::string> container_;
//	std::map<_operations, std::string> op_arr_;
	Error error_manager_;
};


#endif //ABSTRACTVM_PARSER_H
