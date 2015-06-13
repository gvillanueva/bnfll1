/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/1/2015
 *              Modified, 6/8/2015
 * \ingroup     bnfll1
 * \file        bnflex.h
 *
 * \brief       Declares the structure of the Backus-Naur Form lexical analyzer
 *              class.
 */
#ifndef BNFLEX_H
#define BNFLEX_H

#include "token.h"
#include <list>
#include <iostream>

typedef std::vector<Token> TokenList;

class BnfLex
{
public:
    TokenList* analyze(std::istream &istream, const char *filename);
};

#endif // BNFLEX_H
