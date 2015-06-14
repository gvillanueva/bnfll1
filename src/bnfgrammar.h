/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/12/2015
 *              Modified, 6/14/2015
 * \ingroup     bnfll1
 * \file        bnfgrammar.h
 *
 * \brief       Declares the structure of the Backus-Naur Form LL(1) grammar
 *              class.
 */
#ifndef BNFGRAMMAR_H
#define BNFGRAMMAR_H

#include "bnfrule.h"

class BnfGrammar
{
public:
    /// Instantiates a BnfGrammar object.
    BnfGrammar();

    /// Returns a left-factored equivalent of the current BnfGrammar;
    void leftFactor();

    /// Adds a rule to the grammar.
    void addRule(BnfRule* rule);

    /// Determines, by name, whether the grammar contains the rule.
    bool containsRuleName(std::string ruleName);

    /// Returns a pointer to a rule matching the given \p ruleName.
    BnfRule* findRuleByName(std::string ruleName);

    /// Connects non-terminals whose rules did not exist at time of creation.
    void connectNonTerminals();

    /// Returns a copy of the grammar's rules.
    std::vector<BnfRule*>* rules() const;

    /// Prints the grammar in a nice output
    void print();

private:
    /// The list of rules in the grammar
    std::vector<BnfRule*>* m_Rules;
};

#endif // BNFGRAMMAR_H
