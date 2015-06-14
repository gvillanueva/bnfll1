#include "bnfll1.h"
#include "bnfterm.h"
#include "token.h"
#include <QDebug>

BnfLl1::BnfLl1()
{
}

std::map<BnfRule*, std::set<std::string> > BnfLl1::first(BnfGrammar* grammar)
{
    // Clear prevoiusly computed first sets
    if (m_FirstSets.size())
        m_FirstSets.clear();
    m_FinishedRule3.clear();

    std::vector<BnfRule*> rules = grammar->rules();
    for (std::vector<BnfRule*>::iterator rulesIter = rules.begin();
         rulesIter != rules.end(); rulesIter++)
        firstRule1(*rulesIter);

    for (std::vector<BnfRule*>::iterator rulesIter = rules.begin();
         rulesIter != rules.end(); rulesIter++)
        firstRule2(*rulesIter);

    // Perform rule for as many rules as there are (rule 3 could change content)
    for (int i = 0; i < m_FirstSets.size() - rules.size(); i++) {
        for (std::vector<BnfRule*>::iterator rulesIter = rules.begin();
             rulesIter != rules.end(); rulesIter++)
            firstRule3(*rulesIter);
    }

    return m_FirstSets;
}

/*!
 * \brief Adds symbols to rule's first set where the first term in an expression
 *        is a terminal.
 * \param rule The rule under examination.
 */
void BnfLl1::firstRule1(BnfRule* rule)
{
    // For each expression
    for (BnfExpressionVector::iterator exprsIter = rule->expressions()->begin();
         exprsIter != rule->expressions()->end(); exprsIter++)
    {
        // If the expression's first term is a terminal, add it to the first set
        if ((*(*exprsIter)->begin())->isTerm())
            m_FirstSets[rule].insert((*(*exprsIter)->begin())->token());
    }
}

void BnfLl1::firstRule2(BnfRule* rule)
{
    // If the rule is nullable, add λ to the first set
    if (rule->isNullable())
        m_FirstSets[rule].insert("λ");
}

void BnfLl1::firstRule3(BnfRule* rule)//, std::set<std::string>& firstSet)
{
    for (BnfExpressionVector::iterator exprsIter = rule->expressions()->begin();
         exprsIter != rule->expressions()->end(); exprsIter++)
    {
        std::vector<BnfTerm*>::iterator termsIter = (*exprsIter)->begin();
        for (;termsIter != (*exprsIter)->end() && !(*termsIter)->isTerm();
             termsIter++)
        {
            BnfNonTerminal* nonTerm = (BnfNonTerminal*)(*termsIter);
            std::set<std::string> firsts = m_FirstSets[nonTerm->rule()];
            for (std::set<std::string>::iterator firstsIter = firsts.begin();
                 firstsIter != firsts.end(); firstsIter++)
                if (*firstsIter != "λ")
                    m_FirstSets[rule].insert(*firstsIter);
            if (nonTerm->rule() && !nonTerm->rule()->isNullable())
                break;
        }
        if (termsIter == (*exprsIter)->end())
            m_FirstSets[rule].insert("λ");
    }
}

void BnfLl1::printFirstSets()
{
    for (std::map<BnfRule*, std::set<std::string> >::iterator setsIter = m_FirstSets.begin();
         setsIter != m_FirstSets.end(); setsIter++)
    {
        QDebug debugLine = qDebug();
        debugLine << ("<" + setsIter->first->ruleName() + ">").c_str() << "{";
        for (std::set<std::string>::iterator firstsIter = setsIter->second.begin();
             firstsIter != setsIter->second.end(); firstsIter++)
            debugLine << firstsIter->c_str();
        debugLine << "}";
    }
}
