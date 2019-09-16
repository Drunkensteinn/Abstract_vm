//
// Created by Andrei BLIZNIUK on 2019-09-16.
//

#include "../inc/Error.h"

Error::Error() {}

Error::Error(Error const &e) {
	_error_msg = e._error_msg;
}

Error & Error::operator=(Error const &e) {
	if (this != &e) {
		this->_error_msg = e._error_msg;
	}

	return *this;
}

void Error::set_error_msg(const char *msg){
	this->_error_msg = std::string(msg);
}

Error::~Error()
{}