//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#ifndef ABSTRACTVM_LEXER_H
#define ABSTRACTVM_LEXER_H

#include <iostream>
#include <fstream>
#include <istream>

class Lexer
{
public:

	Lexer();
	~Lexer();

	Lexer(Lexer const &l);
	Lexer &operator=(Lexer const &l);

	Lexer(int argc, char **argv);

private:
	FILE *file = NULL;
};


#endif //ABSTRACTVM_LEXER_H
