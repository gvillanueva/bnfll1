/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/1/2015
 *              Modified, 6/14/2015
 * \ingroup     bnfll1
 * \file        bnflex.h
 *
 * \brief       Declares the structure of the Backus-Naur Form lexical analyzer
 *              class.
 */
#ifndef BNFLEX_H
#define BNFLEX_H

#include "token.h"
#include <iostream>

/*!
 * \brief Defines a collection of tokens.
 */
typedef std::vector<Token> TokenList;

/*!
 * \brief Tokenizes a source file formatted according to the Backus-Naur Form.
 */
class BnfLex
{
public:
    /// Returns a list of parsed tokens from the input file.
    TokenList* analyze(std::istream &istream, const char *filename);
};

#endif // BNFLEX_H
