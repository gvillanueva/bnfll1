/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/11/2015
 *              Modified, 6/11/2015
 * \ingroup     bnfll1
 * \file        bnfterm.h
 *
 * \brief       Declares the structure of the class for Backus-Naur Form
 *              expression terms.
 */
#ifndef BNFTERM_H
#define BNFTERM_H

#include "token.h"
#include "bnfrule.h"

/*!
 * \brief Represents a term in a Backus-Naur Form expression.
 */
class BnfTerm
{
    friend class BnfGrammar;
public:
    /// Creates a new term for a BNF expression.
    BnfTerm(Token token);

    /// Creates a new term as a copy of the given term.
    BnfTerm(const BnfTerm& copy);

    /// Copies the given term into this instance of a term.
    BnfTerm& operator=(const BnfTerm& copy);

    /// Compares one term against another for inequality.
    bool operator!=(const BnfTerm& a) const;

    /// Compares one term against another for equality.
    bool operator==(const BnfTerm& a) const;

    /// Compares terms to find which comes earlier in the alphabet.
    bool operator<(const BnfTerm& a) const;

    /// Returns the term's token.
    std::string token() const;

    /// Returns whether the term is a terminal or non-terminal.
    virtual bool isTerm() const;

private:
    /// The term's token.
    std::string m_Token;
};

/*!
 * \brief Represents a non-terminal term in a BNF expression.
 */
class BnfNonTerminal : public BnfTerm
{
public:
    /// Creates a new non-terminal term.
    BnfNonTerminal(Token token, BnfRule* rule);

    /// Creates a new non-terminal from the values in \p copy.
    BnfNonTerminal(const BnfNonTerminal& copy);

    /// Returns the rule this non-terminal points to.
    BnfRule* rule() const;

    /// Sets the rule this non-terminal points to.
    void setRule(BnfRule* value);

    /// Returns false because the term is non-terminal.
    virtual bool isTerm() const;

private:
    /// The rule this non-terminal points to.
    BnfRule* m_Rule;
};

#endif // BNFTERM_H
