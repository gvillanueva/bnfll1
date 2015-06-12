/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/11/2015
 *              Modified, 6/11/2015
 * \ingroup     bnfll1
 * \file        bnfterm.cpp
 *
 * \brief       Defines the implementation of the class for Backus-Naur Form
 *              expression terms.
 */
#include "bnfterm.h"

BnfTerm::BnfTerm(Token token)
    :m_Token(token)
{
}

BnfTerm::BnfTerm(const BnfTerm& copy)
    :m_Token(copy.m_Token)
{
}

BnfTerm& BnfTerm::operator=(const BnfTerm& copy)
{
    if (this != &copy)
        m_Token = copy.m_Token;
    return *this;
}

bool BnfTerm::operator!=(const BnfTerm& a) const
{
    return m_Token.lexeme() != a.m_Token.lexeme();
}

bool BnfTerm::operator==(const BnfTerm& a) const
{
    return m_Token.lexeme() == a.m_Token.lexeme();
}

bool BnfTerm::operator<(const BnfTerm& a) const
{
    return this->m_Token.type() < a.m_Token.type();
}



BnfNonTerminal::BnfNonTerminal(Token token, BnfRule& rule)
    :BnfTerm(token), m_Rule(rule)
{
}

const BnfRule& BnfNonTerminal::rule() const
{
    return m_Rule;
}

void BnfNonTerminal::setRule(const BnfRule& value)
{
    m_Rule = value;
}
