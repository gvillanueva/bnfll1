#include "bnfrule.h"
#include <map>
#include <algorithm>

bool compare_expressions(const BnfExpression a, const BnfExpression b)
{
    return a > b;
}

BnfGrammar BnfGrammar::leftFactor()
{
    // For each rule
    for (std::list<BnfRule>::iterator rule = m_Rules.begin();
         rule != m_Rules.end(); rule++)
    {
        (*rule).leftFactor();
    }
}

std::list<BnfRule> BnfRule::leftFactor()
{
    // Sort expressions so that we don't have to worry that we didn't start with
    // the shortest common left factor
    std::sort(m_Expressions.begin(), m_Expressions.end());
    std::string nameSfx = "'";

    // For each expression in sorted list
    for (BnfExpressionList::iterator exprsIter = m_Expressions.begin();
         exprsIter != m_Expressions.end(); exprsIter++)
    {
        // Hold the return value of mismatch for evaluation
        std::pair<BnfExpression::iterator, BnfExpression::iterator> pair;

        // Holds the list of left factorable expressions
        std::list<BnfLeftFactorPair> leftFactorableExprs;

        // Start mismatching on next expression in the list
        for (BnfExpressionList::iterator otherExprs = exprsIter + 1;
             otherExprs != m_Expressions.end(); otherExprs++)
        {
            pair = std::mismatch(exprsIter->begin(), exprsIter->end(), otherExprs->begin());

            // If the second expressions's mismatched term is not its first term
            // The two expressions can be left factored
            if (pair.second != otherExprs->begin()) {
                // Add the expression being evaluated
                bool allFirstTokensUsed = pair.first == exprsIter->end();
                if (leftFactorableExprs.size() == 0)
                    leftFactorableExprs.push_back(BnfLeftFactorPair(*exprsIter, pair.first));
                leftFactorableExprs.push_back(BnfLeftFactorPair(*otherExprs, pair.second));
            }
            // Since the expressions list is sorted, we know we can break on the
            // first expression without a common left factor
            else
                break;
        }

        // If we have more than one left factorable expression
        if (leftFactorableExprs.size() > 1)
        {
            // Produce left factored expression
            BnfExpression leftFactored;
            std::copy(leftFactorableExprs.begin()->first.begin(),
                      leftFactorableExprs.begin()->second,
                      std::back_inserter(leftFactored));
            leftFactored.push_back(Token(m_RuleName+nameSfx, "NONTERM"));

            // Produce new grammar rule
            BnfRule newRule;
            newRule.setName(m_RuleName+nameSfx);

            // iter == std::pair<BnfExpression, BnfExpression::iterator>
            //
            for (std::list<BnfLeftFactorPair>::iterator iter = leftFactorableExprs.begin();
                 iter != leftFactorableExprs.end(); iter++)
            {
                if (iter->second == iter->first.end())
                    iter->first.clear();
                else
                    iter->first.erase(iter->first.begin(), iter->second);
                newRule.addExpression(iter->first);
            }

            // Add additional "'" to suffix for next left factor
            nameSfx += "'";
        }
    }
}

BnfRule::BnfRule()
{
}
