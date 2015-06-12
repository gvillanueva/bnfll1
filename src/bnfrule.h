#ifndef BNFRULE_H
#define BNFRULE_H

#include <string>
#include <vector>

class BnfTerm;

typedef std::vector<BnfTerm> BnfExpression;
typedef std::vector<BnfExpression> BnfExpressionVector;
typedef std::pair<BnfExpressionVector::iterator, BnfExpression::iterator> BnfLeftFactorPair;

class BnfRule
{
    friend class BnfGrammar;
public:
    BnfRule();
    BnfRule(const BnfRule& copy);
    BnfExpressionVector expressions() const;
    void addExpression(BnfExpression expression);
    std::string ruleName() const;
    void setRuleName(const std::string value);
    std::vector<BnfRule>* leftFactor();

private:
    std::string m_RuleName;
    BnfExpressionVector m_Expressions;
};

class BnfGrammar
{
public:
    /// Returns a left-factored equivalent of the current BnfGrammar;
    void leftFactor();
    void addRule(BnfRule rule);
    void print();

private:
    std::vector<BnfRule> m_Rules;
};

#endif // BNFRULE_H
