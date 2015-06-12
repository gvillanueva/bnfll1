#ifndef BNFRULE_H
#define BNFRULE_H

#include <string>
#include <list>
#include <vector>

class BnfTerm;

typedef std::vector<BnfTerm> BnfExpression;
typedef std::vector<BnfExpression> BnfExpressionList;
typedef std::pair<BnfExpression&, BnfExpression::iterator> BnfLeftFactorPair;

class BnfRule
{
public:
    BnfRule();
    BnfExpressionList expressions() const;
    void addExpression(BnfExpression expression);
    void setName(const std::string value);
    void leftFactor();

private:
    std::string m_RuleName; // or BnfNonTerminal?
    BnfExpressionList m_Expressions;
};

class BnfGrammar
{
public:
    /// Returns a left-factored equivalent of the current BnfGrammar;
    void leftFactor();
    void addRule(BnfRule rule) { m_Rules.push_back(rule); }

private:
    std::list<BnfRule> m_Rules;
};

#endif // BNFRULE_H
