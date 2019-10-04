/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:58:23 by ablizniu          #+#    #+#             */
/*   Updated: 2019/10/01 17:58:23 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <bootstrap.h>
#include <boost/lexical_cast.hpp>
#include "../inc/Error.h"
#include "../inc/parser.h"
#include "../inc/lexer.h"


void execute(IVirtualMachine *m)
{
	try { m->execute(); }
	catch (Error &e) {
		std::cout <<  e.what() << std::endl;
		exit(0);
	}
}

int main(int argc, char **argv)
{
	IVirtualMachine *lexer = new Lexer(argc, argv);
	execute(lexer);

	IVirtualMachine *parser = new Parser(lexer);
	execute(parser);
	return (0);
}