#ifndef BNFTERM_H
#define BNFTERM_H

#include "token.h"
#include "bnfrule.h"

class BnfTerm {
public:
    BnfTerm(Token token);
    BnfTerm(const BnfTerm& copy);
    BnfTerm& operator=(const BnfTerm& copy);
    bool operator!=(const BnfTerm& a) const;
    bool operator==(const BnfTerm& a) const;
    bool operator<(const BnfTerm& a) const;

    Token m_Token;
};

class BnfNonTerminal : BnfTerm
{
public:
    BnfNonTerminal(Token token, BnfRule& rule);
    const BnfRule& rule() const;
    void setRule(const BnfRule& value);
private:
    BnfRule& m_Rule;
};

#endif // BNFTERM_H
