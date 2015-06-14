#ifndef BNFRULE_H
#define BNFRULE_H

#include <string>
#include <vector>

class BnfTerm;

typedef std::vector<BnfTerm*> BnfExpression;
typedef std::vector<BnfExpression*> BnfExpressionVector;
typedef std::pair<BnfExpressionVector::iterator, BnfExpression::iterator> BnfLeftFactorPair;

class BnfRule
{
    friend class BnfGrammar;
public:
    BnfRule();
    BnfRule(const BnfRule& copy);
    BnfExpressionVector* expressions() const;
    void addExpression(BnfExpression* expression);
    std::string ruleName() const;
    void setRuleName(const std::string value);
    bool isNullable() const;
    std::vector<BnfRule*>* leftFactor();

private:
    std::string m_RuleName;
    BnfExpressionVector* m_Expressions;
    bool m_HasLambda;
};

#endif // BNFRULE_H
