//
// Created by Andrei BLIZNIUK on 2019-09-16.
//

#include "../inc/Error.h"

Error::Error() {}

Error::Error(const char *m):_error_msg(m) {}

Error::Error(Error const &e) {
	_error_msg = e._error_msg;
}

Error & Error::operator=(Error const &e) {
	if (this != &e) {
		this->_error_msg = e._error_msg;
	}

	return *this;
}

Error::~Error()
{}