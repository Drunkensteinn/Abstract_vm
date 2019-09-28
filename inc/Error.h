#ifndef ABSTRACTVM_ERROR_H
#define ABSTRACTVM_ERROR_H

#include <iostream>

class Error:std::exception
{
public:
	Error();
	Error(const char *m);
	Error(Error const &e);
	Error(std::string const & e);
	Error &operator=(Error const &e);
	virtual ~Error();
	const char * what() const throw() {
		return _error_msg.c_str();
	}
private:
	std::string _error_msg;
};


#endif //ABSTRACTVM_ERROR_H
