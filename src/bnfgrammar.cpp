#include "bnfgrammar.h"
#include "bnfterm.h"
#include <QDebug>
#include <typeinfo>

void BnfGrammar::leftFactor()
{
    // For each rule
    for (std::vector<BnfRule*>::iterator rule = m_Rules.begin();
         rule != m_Rules.end(); rule++)
    {
        std::vector<BnfRule*>* leftFactoredRules = (*rule)->leftFactor();
        if (leftFactoredRules)
        {
            for (int i = 0; i < leftFactoredRules->size(); i++)
                rule = m_Rules.insert(rule+1, leftFactoredRules->at(i));
        }
    }
}

void BnfGrammar::addRule(BnfRule* rule)
{
    m_Rules.push_back(rule);
}

/*!
 * \brief Determines, by name, whether the grammar contains the rule.
 * \param rule The rule to search for.
 * \return true if a rule in the grammar has the same name as \p rule.
 */
bool BnfGrammar::containsRuleName(std::string ruleName)
{
    for (std::vector<BnfRule*>::iterator ruleIter = m_Rules.begin();
         ruleIter != m_Rules.end(); ruleIter++)
    {
        if (ruleName == (*ruleIter)->ruleName())
            return true;
    }

    return false;
}

BnfRule* BnfGrammar::findRuleByName(std::string ruleName)
{
    for (std::vector<BnfRule*>::iterator ruleIter = m_Rules.begin();
         ruleIter != m_Rules.end(); ruleIter++)
    {
        if (ruleName== (*ruleIter)->ruleName())
            return *ruleIter;
    }

    return NULL;
}

void BnfGrammar::connectNonTerminals()
{
    for (std::vector<BnfRule*>::iterator rule = m_Rules.begin();
         rule != m_Rules.end(); rule++)
    {
        QDebug debugLine = qDebug();
        debugLine << ("<" + (*rule)->ruleName() + ">").c_str() << "->";

        for (std::vector<BnfExpression*>::iterator expr = (*rule)->m_Expressions->begin();
             expr != (*rule)->m_Expressions->end(); expr++) {
            for (std::vector<BnfTerm*>::iterator term = (*expr)->begin();
                 term != (*expr)->end(); term++){
                if (!(*term)->isTerm()) {
                    BnfNonTerminal* nonTerm = (BnfNonTerminal*)*term;
                    if (!nonTerm->rule())
                        nonTerm->setRule(findRuleByName(nonTerm->token()));
                }
            }
            if (expr+1 != (*rule)->m_Expressions->end())
                debugLine << "|";
        }
    }
}

std::vector<BnfRule*> BnfGrammar::rules() const
{
    return m_Rules;
}

void BnfGrammar::print()
{
    for (std::vector<BnfRule*>::iterator rule = m_Rules.begin();
         rule != m_Rules.end(); rule++)
    {
        QDebug debugLine = qDebug();
        debugLine << ("<" + (*rule)->ruleName() + ">").c_str() << "->";

        for (std::vector<BnfExpression*>::iterator expr = (*rule)->m_Expressions->begin();
             expr != (*rule)->m_Expressions->end(); expr++) {
            for (std::vector<BnfTerm*>::iterator term = (*expr)->begin();
                 term != (*expr)->end(); term++){
                if ((*term)->isTerm())
                    debugLine << ("\"" + (*term)->m_Token + "\"").c_str();
                else
                    debugLine << ("<" + (*term)->m_Token + ">").c_str();
            }
            if (expr+1 != (*rule)->m_Expressions->end())
                debugLine << "|";
        }
    }
}
