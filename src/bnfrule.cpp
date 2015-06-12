#include "bnfrule.h"
#include "bnfterm.h"
#include <algorithm>
#include <QDebug>

bool compare_expressions(const BnfExpression a, const BnfExpression b)
{
    return a > b;
}

BnfRule::BnfRule()
{
    qDebug() << __func__ << m_RuleName.c_str();
}

BnfRule::BnfRule(const BnfRule& copy)
    :m_RuleName(copy.m_RuleName), m_Expressions(copy.m_Expressions)
{
    qDebug() << __func__ << "copy" << m_RuleName.c_str();
}

BnfExpressionVector BnfRule::expressions() const
{
    qDebug() << __func__ << "op=" << m_RuleName.c_str();
}

void BnfRule::addExpression(BnfExpression expression)
{
    m_Expressions.push_back(expression);
}

void BnfRule::setName(const std::string value)
{
    m_RuleName = value;
}

void BnfRule::leftFactor()
{
    // Sort expressions so that we don't have to worry that we didn't start with
    // the shortest common left factor
    std::sort(m_Expressions.begin(), m_Expressions.end());
    std::string nameSfx = "'";

    // For each expression in sorted vector
    for (BnfExpressionVector::iterator exprsIter = m_Expressions.begin();
         exprsIter != m_Expressions.end(); exprsIter++)
    {
        // Hold the return value of mismatch for evaluation
        std::pair<BnfExpression::iterator, BnfExpression::iterator> pair;

        // Holds the vector of left factorable expressions
        std::vector<BnfLeftFactorPair> leftFactorableExprs;

        // Start mismatching on next expression in the vector
        for (BnfExpressionVector::iterator otherExprs = exprsIter + 1;
             otherExprs != m_Expressions.end(); otherExprs++)
        {
            pair = std::mismatch(exprsIter->begin(), exprsIter->end(), otherExprs->begin());

            // If the second expressions's mismatched term is not its first term
            // The two expressions can be left factored
            if (pair.second != otherExprs->begin()) {
                // Add the expression being evaluated
                if (leftFactorableExprs.size() == 0)
                    leftFactorableExprs.push_back(BnfLeftFactorPair(exprsIter, pair.first));
                leftFactorableExprs.push_back(BnfLeftFactorPair(otherExprs, pair.second));
            }
            // Since the expressions vector is sorted, we know we can break on
            // the first expression without a common left factor
            else
                break;
        }

        // If we have more than one left factorable expression
        if (leftFactorableExprs.size() > 1)
        {
            // Produce left factored expression
            BnfExpression leftFactored(exprsIter->begin(), leftFactorableExprs.begin()->second);
            leftFactored.push_back(Token(m_RuleName+nameSfx, "NONTERM"));

            // Produce new grammar rule
            BnfRule newRule;
            newRule.setName(m_RuleName+nameSfx);

            for (std::vector<BnfLeftFactorPair>::iterator iter = leftFactorableExprs.begin();
                 iter != leftFactorableExprs.end();)
            {
                iter->first->erase(iter->first->begin(), iter->second);
                if (iter->first->size() != 0)
                    newRule.addExpression(*iter->first);
                m_Expressions.erase(iter++->first);
            }

            // Add additional "'" to suffix for next left factor
            nameSfx += "'";
        }
    }
}



void BnfGrammar::leftFactor()
{
    // For each rule
    for (std::vector<BnfRule>::iterator rule = m_Rules.begin();
         rule != m_Rules.end(); rule++)
    {
        (*rule).leftFactor();
    }
}

void BnfGrammar::addRule(BnfRule rule)
{
    m_Rules.push_back(rule);
}
