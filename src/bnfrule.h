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
    BnfExpressionList expressions() const { return m_Expressions; }
    void addExpression(BnfExpression expression) { m_Expressions.push_back(expression); }
    void setName(const std::string value) { m_RuleName = value; }
    std::list<BnfRule> leftFactor();

private:
    std::string m_RuleName; // or BnfNonTerminal?
    BnfExpressionList m_Expressions;
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
