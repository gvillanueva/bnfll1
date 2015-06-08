/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/1/2015
 *              Modified, 6/8/2015
 * \ingroup     bnfll1
 * \file        bnfsyn.h
 *
 * \brief       Declares the structure of the Backus-Naur Form syntax analyzer
 *              class.
 */
#ifndef BNFSYN_H
#define BNFSYN_H

#include "token.h"
#include <list>
typedef std::list<Token> TokenList;

/*!
 * \brief The BnfSyn class is absolutely not thread-safe.
 */
class BnfSyn
{
public:
    BnfSyn();
    bool analyze(const TokenList& tokens);

private:
    bool readType(std::string lexeme);
    bool syntax();
    bool rule();
    bool expression();
    bool lineEnd();
    bool list();
    bool term();
    bool literal();

    std::list<Token>::const_iterator m_Iter;
};

#endif // BNFSYN_H
