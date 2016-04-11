/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/9/2015
 *              Modified, 6/14/2015
 * \ingroup     bnfll1
 * \file        bnfrule.cpp
 *
 * \brief       Implements the Backus-Naur Form LL(1) grammar rule class.
 */
#include "bnfrule.h"
#include "bnfterm.h"
#include <algorithm>
#include <iostream>
/*!
 * \brief This is a predicate to compare expressions for sorting.
 * \param a The first expression.
 * \param b The second expression.
 * \return true if the first expression is short in length, or its terms would
 *         first, alphabetically.
 */
bool compare_expressions(BnfExpression* a, BnfExpression* b)
{
    // Shortcut to return true if the size is smaller.
    if (a->size() < b->size())
        return true;
    else if (a->size() > b->size())
        return false;
    //Otherwise sort alphabetically by term
    else
    {
        BnfExpression::iterator aIter = a->begin(), bIter = b->begin();
        while(aIter != a->end() && bIter != b->end())
            if ((*aIter)->token() != (*bIter)->token())
                return (*aIter)->token() < (*bIter)->token();
        return false;
    }
}

/*!
 * \brief This is a binary predicate for comparing terms.
 * \param a The first term.
 * \param b The second term.
 * \return Return whether the first term's token matches the second term's token.
 */
bool compare_terms(BnfTerm* a, BnfTerm* b)
{
    return a->token() == b->token();
}

/*!
 * \brief Instantiates a BnfRule object.
 */
BnfRule::BnfRule()
    :m_HasLambda(false)
{
    m_Expressions = new BnfExpressionVector;
}

/*!
 * \brief BnfRule::BnfRule
 * \param copy
 */
BnfRule::BnfRule(const BnfRule& copy)
    :m_RuleName(copy.m_RuleName), m_Expressions(copy.m_Expressions),
     m_HasLambda(copy.m_HasLambda)
{
}

/*!
 * \brief Gets the expressions within a BnfRule.
 * \return A pointer to the rule's vector of expressions.
 */
BnfExpressionVector* BnfRule::expressions() const
{
    return m_Expressions;
}

/*!
 * \brief Adds an expression to the rule.
 * \param expression The expression to add to the rule.
 */
void BnfRule::addExpression(BnfExpression* expression)
{
    // If the expression contains any terms, add it
    if (expression->size())
        m_Expressions->push_back(expression);
    // If the expression has no terms, treat it like a lambda production
    else if (!m_HasLambda)
    {
        BnfExpression* lambdaExpr = new BnfExpression;
        lambdaExpr->push_back(new BnfTerm(Token("?", "TERM")));
        m_Expressions->push_back(lambdaExpr);
        m_HasLambda = true;
    }
}

/*!
 * \brief Gets the name of the rule.
 * \return A std::string identifying the rule.
 */
std::string BnfRule::ruleName() const
{
    return m_RuleName;
}

/*!
 * \brief Sets the name of the rule.
 * \param value The new name to assign the rule.
 */
void BnfRule::setRuleName(const std::string value)
{
    m_RuleName = value;
}

/*!
 * \brief Gets whether the rule is nullable.
 * \return true if the rule contains any lambda productions, otherwise false.
 */
bool BnfRule::isNullable() const
{
    return m_HasLambda;
}

/*!
 * \brief Returns the left factored rules of the rule.
 * \return A list of left-factored rules, if left factors exist, otherwise null.
 */
std::vector<BnfRule*>* BnfRule::leftFactor()
{
    // Sort expressions so that we don't have to worry that we didn't start with
    // the shortest common left factor
    std::sort(m_Expressions->begin(), m_Expressions->end(), compare_expressions);
    std::string nameSfx = "'";
    std::vector<BnfRule*>* leftFactoredRules = new std::vector<BnfRule*>;

    // For each expression in sorted vector
    for (BnfExpressionVector::iterator exprsIter = m_Expressions->begin();
         exprsIter != m_Expressions->end();)
    {
        bool leftFactored = false;
        BnfExpression::iterator firstLeft;

        std::pair<BnfExpression::iterator, BnfExpression::iterator> pair;

        // Produce new grammar rule
        BnfRule *newRule = new BnfRule;
        newRule->setRuleName(m_RuleName+nameSfx);

        // Start mismatching on next expression in the vector
        for (BnfExpressionVector::iterator otherExprs = exprsIter + 1;
             otherExprs != m_Expressions->end();)
        {
            // Hold the return value of mismatch for evaluation
            pair = std::mismatch((*exprsIter)->begin(), (*exprsIter)->end(),
                                 (*otherExprs)->begin(), compare_terms);

            // If the second expressions's mismatched term is not its first term
            // The two expressions can be left factored
            if (pair.second != (*otherExprs)->begin()) {
                firstLeft = pair.first;
                leftFactored = true;

                // If left factored, remove from original rule
                (*otherExprs)->erase((*otherExprs)->begin(), pair.second);
                newRule->addExpression(*otherExprs);
                otherExprs = m_Expressions->erase(otherExprs);
            }
            // Since the expressions vector is sorted, we know we can break on
            // the first expression without a common left factor
            else
                break;
       }

        // If current expression was left factored, remove from original rule
        if (leftFactored)
        {
            BnfExpression* leftFactored = //new BnfExpression;
                    new BnfExpression((*exprsIter)->begin(), firstLeft);
            leftFactored->push_back(new BnfNonTerminal(Token(m_RuleName+nameSfx, "NONTERM"), newRule));
            m_Expressions->push_back(leftFactored);

            // Add right factors to new rule
            (*exprsIter)->erase((*exprsIter)->begin(), firstLeft);
            newRule->addExpression(*exprsIter);
            leftFactoredRules->push_back(newRule);

            nameSfx += "'";
            exprsIter = m_Expressions->erase(exprsIter);
        }
        else
            exprsIter++;
    }

    if (leftFactoredRules->size() > 0)
        return leftFactoredRules;
    else
    {
        delete leftFactoredRules;
        return NULL;
    }
}
