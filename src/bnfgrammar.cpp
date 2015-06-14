/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/12/2015
 *              Modified, 6/14/2015
 * \ingroup     bnfll1
 * \file        bnfgrammar.cpp
 *
 * \brief       Implements the Backus-Naur Form LL(1) grammar class.
 */
#include "bnfgrammar.h"
#include "bnfterm.h"
#include <QDebug>
#include <typeinfo>

/*!
 * \brief Instantiates a BnfGrammar object.
 */
BnfGrammar::BnfGrammar()
{
    m_Rules = new std::vector<BnfRule*>;
}

/*!
 * \brief Transforms the grammar to remove left factors.
 */
void BnfGrammar::leftFactor()
{
    // For each rule
    for (std::vector<BnfRule*>::iterator rule = m_Rules->begin();
         rule != m_Rules->end(); rule++)
    {
        // Left factor the rule
        std::vector<BnfRule*>* leftFactoredRules = (*rule)->leftFactor();

        // If there were new rules created due to left factor removal
        if (leftFactoredRules)
        {
            // Add the new rules
            for (unsigned int i = 0; i < leftFactoredRules->size(); i++)
                rule = m_Rules->insert(rule+1, leftFactoredRules->at(i));
        }
    }
}

/*!
 * \brief Adds a rule to the grammar.
 * \param rule The rule to add to the grammar.
 */
void BnfGrammar::addRule(BnfRule* rule)
{
    m_Rules->push_back(rule);
}

/*!
 * \brief Determines, by name, whether the grammar contains the rule.
 * \param rule The rule to search for.
 * \return true if a rule in the grammar has the same name as \p rule.
 */
bool BnfGrammar::containsRuleName(std::string ruleName)
{
    for (std::vector<BnfRule*>::iterator ruleIter = m_Rules->begin();
         ruleIter != m_Rules->end(); ruleIter++)
    {
        if (ruleName == (*ruleIter)->ruleName())
            return true;
    }

    return false;
}

/*!
 * \brief Returns a pointer to a rule matching the given \p ruleName.
 * \param ruleName The ruleName to match against.
 * \return A pointer to the rule matching \p ruleName, or NULL if no match
 *         exists.
 */
BnfRule* BnfGrammar::findRuleByName(std::string ruleName)
{
    // Iterate all the rules in the grammar
    for (std::vector<BnfRule*>::iterator ruleIter = m_Rules->begin();
         ruleIter != m_Rules->end(); ruleIter++)
    {
        // Return the current rule if its name matches \p ruleName
        if (ruleName== (*ruleIter)->ruleName())
            return *ruleIter;
    }

    // Return NULL if no matching rule can be found
    return NULL;
}

/*!
 * \brief Connects non-terminals whose rules did not exist at time of creation.
 */
void BnfGrammar::connectNonTerminals()
{
    // Iterate all rules in the grammar.
    for (std::vector<BnfRule*>::iterator rule = m_Rules->begin();
         rule != m_Rules->end(); rule++)
    {
        for (std::vector<BnfExpression*>::iterator expr = (*rule)->m_Expressions->begin();
             expr != (*rule)->m_Expressions->end(); expr++) {
            for (std::vector<BnfTerm*>::iterator term = (*expr)->begin();
                 term != (*expr)->end(); term++) {
                if (!(*term)->isTerm())
                {
                    BnfNonTerminal* nonTerm = (BnfNonTerminal*)*term;
                    if (!nonTerm->rule())
                        nonTerm->setRule(findRuleByName(nonTerm->token()));
                }
            }
        }
    }
}

/*!
 * \brief Returns the rules in the grammar.
 * \return Pointer to the grammar's vector of rules.
 */
std::vector<BnfRule*>* BnfGrammar::rules() const
{
    return m_Rules;
}

/*!
 * \brief Prints the grammar in a nice output.
 */
void BnfGrammar::print()
{
    // Iterate each rule in the grammar
    for (std::vector<BnfRule*>::iterator rule = m_Rules->begin();
         rule != m_Rules->end(); rule++)
    {
        // Output the rule name
        QDebug debugLine = qDebug();
        debugLine << ("<" + (*rule)->ruleName() + ">").c_str() << "->";

        // Iterate the expressions in the rul
        for (std::vector<BnfExpression*>::iterator expr = (*rule)->m_Expressions->begin();
             expr != (*rule)->m_Expressions->end(); expr++)
        {
            // Iterate the terms in the expression
            for (std::vector<BnfTerm*>::iterator term = (*expr)->begin();
                 term != (*expr)->end(); term++)
            {
                // If the term is terminal, wrap it in ""
                if ((*term)->isTerm())
                    debugLine << ("\"" + (*term)->m_Token + "\"").c_str();
                // If the term is non-terminal, wrap it in <>
                else
                    debugLine << ("<" + (*term)->m_Token + ">").c_str();
            }

            // If this is not the last expression, add a "|"
            if (expr+1 != (*rule)->m_Expressions->end())
                debugLine << "|";
        }
    }
}
