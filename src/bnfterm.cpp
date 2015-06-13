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
#include <QDebug>

BnfTerm::BnfTerm(Token token)
    :m_Token(token.lexeme())
{
    qDebug() << __func__ << m_Token.c_str();
}

BnfTerm::BnfTerm(const BnfTerm& copy)
    :m_Token(copy.m_Token)
{
    qDebug() << __func__ << "copy" << m_Token.c_str();
}

BnfTerm& BnfTerm::operator=(const BnfTerm& copy)
{
    qDebug() << __func__ << "op=" << m_Token.c_str();
    if (this != &copy)
        m_Token = copy.m_Token;
    return *this;
}

bool BnfTerm::operator!=(const BnfTerm& a) const
{
    return m_Token != a.m_Token;
}

bool BnfTerm::operator==(const BnfTerm& a) const
{
    return m_Token == a.m_Token;
}

bool BnfTerm::operator<(const BnfTerm& a) const
{
    return this->m_Token < a.m_Token;
}

std::string BnfTerm::token() const
{
    return m_Token;
}

bool BnfTerm::isTerm() const
{
    return true;
}


BnfNonTerminal::BnfNonTerminal(Token token, BnfRule* rule)
    :BnfTerm(token), m_Rule(rule)
{
    qDebug() << __func__ << token.lexeme().c_str();
}

BnfNonTerminal::BnfNonTerminal(const BnfNonTerminal& copy)
    :BnfTerm(copy), m_Rule(copy.m_Rule)
{
    qDebug() << __func__ << "copy" << token().c_str();
}

BnfRule* BnfNonTerminal::rule() const
{
    return m_Rule;
}

void BnfNonTerminal::setRule(BnfRule* value)
{
    m_Rule = value;
}

bool BnfNonTerminal::isTerm() const
{
    return false;
}
