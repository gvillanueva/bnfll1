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

class BnfTerm
{
    friend class BnfGrammar;
public:
    BnfTerm(Token token);
    BnfTerm(const BnfTerm& copy);
    BnfTerm& operator=(const BnfTerm& copy);
    bool operator!=(const BnfTerm& a) const;
    bool operator==(const BnfTerm& a) const;
    bool operator<(const BnfTerm& a) const;
    std::string token() const;
    virtual bool isTerm() const;

private:
    std::string m_Token;
};

class BnfNonTerminal : public BnfTerm
{
public:
    BnfNonTerminal(Token token, BnfRule* rule);
    BnfNonTerminal(const BnfNonTerminal& copy);
    BnfRule* rule() const;
    void setRule(BnfRule* value);
    virtual bool isTerm() const;

private:
    BnfRule* m_Rule;
};

#endif // BNFTERM_H
