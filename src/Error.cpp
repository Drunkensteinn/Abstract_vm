/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:59:07 by ablizniu          #+#    #+#             */
/*   Updated: 2019/10/01 17:59:07 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Error.h"

Error::Error() {}

Error::Error(const char *m):_error_msg(m) {}

Error::Error(Error const &e) {
	_error_msg = e._error_msg;
}

Error::Error(std::string const &e):_error_msg(e) {}

Error & Error::operator=(Error const &e) {
	if (this != &e) {
		this->_error_msg = e._error_msg;
	}

	return *this;
}

Error::~Error()
{}