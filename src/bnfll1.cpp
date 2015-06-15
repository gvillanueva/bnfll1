/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/12/2015
 *              Modified, 6/14/2015
 * \ingroup     bnfll1
 * \file        bnfsyn.cpp
 *
 * \brief       Implements the Backus-Naur Form syntax analyzer class.
 */
#include "bnfll1.h"
#include "bnfterm.h"
#include "token.h"
#include <iostream>
#include <iomanip>

/*!
 * \brief Instantiates a new LL(1) compiler generator.
 */
BnfLl1::BnfLl1()
{
    m_FirstSets = new std::map<BnfRule*, std::set<std::string> >;
}

/*!
 * \brief Computes the first set from the given grammar.
 * \param grammar The input grammar to compute a first set for.
 * \return A collection of string sets mapped to a rule in the grammar.
 */
std::map<BnfRule*, std::set<std::string> >* BnfLl1::first(BnfGrammar* grammar)
{
    // Clear prevoiusly computed first sets
    if (m_FirstSets->size())
        m_FirstSets->clear();

    std::vector<BnfRule*>* rules = grammar->rules();
    for (std::vector<BnfRule*>::iterator rulesIter = rules->begin();
         rulesIter != rules->end(); rulesIter++)
        firstRule1(*rulesIter);

    for (std::vector<BnfRule*>::iterator rulesIter = rules->begin();
         rulesIter != rules->end(); rulesIter++)
        firstRule2(*rulesIter);

    // Perform rule for as many rules as there are (rule 3 could change content)
    for (unsigned int i = 0; i < m_FirstSets->size() - rules->size(); i++) {
        for (std::vector<BnfRule*>::iterator rulesIter = rules->begin();
             rulesIter != rules->end(); rulesIter++)
            firstRule3(*rulesIter);
    }

    return m_FirstSets;
}

/*!
 * \brief Implements the first rule for generating a first set.
 * \param rule The rule under examination.
 *        Adds symbols to rule's first set where the first term in an expression
 *        is a terminal.
 */
void BnfLl1::firstRule1(BnfRule* rule)
{
    // For each expression
    for (BnfExpressionVector::iterator exprsIter = rule->expressions()->begin();
         exprsIter != rule->expressions()->end(); exprsIter++)
    {
        // If the expression's first term is a terminal, add it to the first set
        if ((*(*exprsIter)->begin())->isTerm())
            (*m_FirstSets)[rule].insert((*(*exprsIter)->begin())->token());
    }
}

/*!
 * \brief Implements the second rule for generating a first set.
 * \param rule The rule under examination.
 *        Adds lambda to a rule's first set where the rule is nullable.
 */
void BnfLl1::firstRule2(BnfRule* rule)
{
    // If the rule is nullable, add λ to the first set
    if (rule->isNullable())
        (*m_FirstSets)[rule].insert("?");
}

/*!
 * \brief Implements the third rule for generating a first set.
 * \param rule The rule under examination.
 *        Assesses each term of a rule's expressions. If the term is a
 *        non-terminal, that first set of that non-terminal's rule is added to
 *        the first set of \p rule.  If the term is non-nullable, rule 3 is
 *        finished.  Otherwise, we continue iterating until we reach a terminal
 *        term, or a non-terminal whose rule is non-nullable,
 */
void BnfLl1::firstRule3(BnfRule* rule)
{
    // Iterate each expression in rule
    for (BnfExpressionVector::iterator exprsIter = rule->expressions()->begin();
         exprsIter != rule->expressions()->end(); exprsIter++)
    {
        // Asses each term in the expression, until we run out of terms or the
        // current term is a terminal
        std::vector<BnfTerm*>::iterator termsIter = (*exprsIter)->begin();
        for (;termsIter != (*exprsIter)->end() && !(*termsIter)->isTerm();
             termsIter++)
        {
            // Cast term to non-terminal (guaranteed safe)
            BnfNonTerminal* nonTerm = (BnfNonTerminal*)(*termsIter);

            // Create copy of first set for the non-terminal's rule
            std::set<std::string> firsts = (*m_FirstSets)[nonTerm->rule()];

            // Add all of the first symbols except lambda
            for (std::set<std::string>::iterator firstsIter = firsts.begin();
                 firstsIter != firsts.end(); firstsIter++) {
                if (*firstsIter != "?")
                    (*m_FirstSets)[rule].insert(*firstsIter);
            }

            // If non-terminal's rule is non-nullable, break the loop
            if (nonTerm->rule() && !nonTerm->rule()->isNullable())
                break;
        }

        // If we reached the end, there were no non-nullable rules for the
        // non-terminals -- add lamdba to current rule's first set.
        if (termsIter == (*exprsIter)->end())
            (*m_FirstSets)[rule].insert("?");
    }
}

/*!
 * \brief Prints the result of the last first() operation.
 */
void BnfLl1::printFirstSets()
{
    // Iterate the all the rules with first sets
    for (std::map<BnfRule*, std::set<std::string> >::iterator setsIter = m_FirstSets->begin();
         setsIter != m_FirstSets->end(); setsIter++)
    {
        std::cout  << "<" << setsIter->first->ruleName() << "> " << "{";
        for (std::set<std::string>::iterator firstsIter = setsIter->second.begin();
             firstsIter != setsIter->second.end(); firstsIter++)
            std::cout << " \"" << *firstsIter << "\" ";
        std::cout << "}" << std::endl;
    }
}
