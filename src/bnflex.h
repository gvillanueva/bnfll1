#ifndef BNFLEX_H
#define BNFLEX_H

#include "token.h"
#include <list>
#include <iostream>

typedef std::list<Token> TokenList;

class BnfLex
{
public:
    TokenList* analyze(std::istream &istream, const char *filename);
};

#endif // BNFLEX_H
