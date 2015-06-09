#ifndef BNFRULE_H
#define BNFRULE_H

#include "token.h"
#include <string>
#include <list>
#include <vector>

class BnfTerm {
public:
    BnfTerm(Token token) : token(token){}
    BnfTerm(const BnfTerm& copy) : token(copy.token) {}
    BnfTerm& operator=(const BnfTerm& copy) { token = copy.token; return *this; }
    bool operator!=(const BnfTerm& a) const { return token.lexeme() != a.token.lexeme(); }
    bool operator==(const BnfTerm& a) const { return token.lexeme() == a.token.lexeme(); }
    Token token;
    bool operator<(const BnfTerm& a) const
    {
        return this->token.type() < a.token.type();
    }
};
class BnfLiteral : BnfTerm {};
class BnfNonTerminal : BnfTerm {};

typedef std::vector<BnfTerm> BnfExpression;
typedef std::list<BnfExpression> BnfExpressionList;

class BnfRule
{
public:
    BnfRule();
    std::list<BnfExpression> expressions() const { return m_Expressions; }
    void addExpression(BnfExpression expression) { m_Expressions.push_back(expression); }
    void setName(const std::string value) { m_RuleName = value; }
    std::list<BnfRule> leftFactor();

private:
    std::string m_RuleName; // or BnfNonTerminal?
    std::list<BnfExpression> m_Expressions;
};

class BnfGrammar
{
public:
    /// Returns a left-factored equivalent of the current BnfGrammar;
    BnfGrammar leftFactor();
    void addRule(BnfRule rule) { m_Rules.push_back(rule); }

private:
    std::list<BnfRule> m_Rules;
};

#endif // BNFRULE_H
