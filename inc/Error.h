//
// Created by Andrei BLIZNIUK on 2019-09-16.
//

#ifndef ABSTRACTVM_ERROR_H
#define ABSTRACTVM_ERROR_H

#include <iostream>

class Error:std::exception
{
public:
	Error();
	Error(Error const &e);
	Error &operator=(Error const &e);
	virtual ~Error();
	const char * what() const throw() {
		return _error_msg.c_str();
	}

	void set_error_msg(const char *msg);

private:
	std::string _error_msg;
};


#endif //ABSTRACTVM_ERROR_H
