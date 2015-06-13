#ifndef BNFGRAMMAR_H
#define BNFGRAMMAR_H

#include "bnfrule.h"

class BnfGrammar
{
public:
    /// Returns a left-factored equivalent of the current BnfGrammar;
    void leftFactor();
    void addRule(BnfRule* rule);
    bool containsRuleName(std::string ruleName);
    BnfRule* findRuleByName(std::string ruleName);
    void connectNonTerminals();
    void print();

private:
    std::vector<BnfRule*> m_Rules;
};

#endif // BNFGRAMMAR_H
