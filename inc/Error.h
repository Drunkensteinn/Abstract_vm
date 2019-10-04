/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:59:19 by ablizniu          #+#    #+#             */
/*   Updated: 2019/10/01 17:59:52 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H

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


#endif
