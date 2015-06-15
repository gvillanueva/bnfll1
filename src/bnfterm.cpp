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
#include <iostream>

/*!
 * \brief Creates a new term for a BNF expression.
 * \param token The token that created this term.
 */
BnfTerm::BnfTerm(Token token)
    :m_Token(token.lexeme())
{
}

/*!
 * \brief Creates a new term as a copy of the given term.
 * \param copy The copy whose values will initialize this instance.
 */
BnfTerm::BnfTerm(const BnfTerm& copy)
    :m_Token(copy.m_Token)
{
}

/*!
 * \brief Copies the given term into this instance of a term.
 * \param copy The copy whose values will initialize this instance.
 * \return this instance of a BnfTerm.
 */
BnfTerm& BnfTerm::operator=(const BnfTerm& copy)
{
    if (this != &copy)
        m_Token = copy.m_Token;
    return *this;
}

/*!
 * \brief Compares one term against another for inequality.
 * \param a The term to compare against.
 * \return Returns true if the term's token characters mismatch, otherwise false.
 */
bool BnfTerm::operator!=(const BnfTerm& a) const
{
    return m_Token != a.m_Token;
}

/*!
 * \brief Compares one term against another for equality.
 * \param a The term to compare against.
 * \return Returns true if the term's token characters match, otherwise false.
 */
bool BnfTerm::operator==(const BnfTerm& a) const
{
    return m_Token == a.m_Token;
}

/*!
 * \brief Compares terms to find which comes earlier in the alphabet.
 * \param a The term to compare against.
 * \return Returns true if this token would come before \p a, otherwise false.
 */
bool BnfTerm::operator<(const BnfTerm& a) const
{
    return this->m_Token < a.m_Token;
}

/*!
 * \brief Returns the term's token.
 * \return The characters of the token that generated this term.
 */
std::string BnfTerm::token() const
{
    return m_Token;
}

/*!
 * \brief Returns whether the term is a terminal or non-terminal.
 * \return true.
 */
bool BnfTerm::isTerm() const
{
    return true;
}

/*!
 * \brief Creates a new non-terminal term.
 * \param token The token that generated this term.
 * \param rule The rule this non-terminal points to.
 */
BnfNonTerminal::BnfNonTerminal(Token token, BnfRule* rule)
    :BnfTerm(token), m_Rule(rule)
{
}

/*!
 * \brief Creates a new non-terminal from the values in \p copy.
 * \param copy The copy whose values will initialize this instance.
 */
BnfNonTerminal::BnfNonTerminal(const BnfNonTerminal& copy)
    :BnfTerm(copy), m_Rule(copy.m_Rule)
{
}

/*!
 * \brief Returns the rule this non-terminal points to.
 * \return Pointer to the non-terminal's rule object.
 */
BnfRule* BnfNonTerminal::rule() const
{
    return m_Rule;
}

/*!
 * \brief Sets the rule this non-terminal points to.
 * \param value Pointer to the new rule.
 */
void BnfNonTerminal::setRule(BnfRule* value)
{
    m_Rule = value;
}

/*!
 * \brief Returns whether the term is a terminal or non-terminal.
 * \return false.
 */
bool BnfNonTerminal::isTerm() const
{
    return false;
}
