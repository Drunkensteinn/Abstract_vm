//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#include "../inc/lexer.h"


Lexer::Lexer() {}

Lexer::~Lexer() {}

Lexer::Lexer(Lexer const &l) {
	file = l.file;
}

Lexer& Lexer::operator=(Lexer const &l)
{
	if (this != &l) {
		file = l.file;
	}
	return *this;
}

Lexer::Lexer(int argc, char **argv)
{
	if (argc < 2)
		file = fopen(argv[1], "r");

}