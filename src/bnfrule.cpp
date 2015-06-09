#include "bnfrule.h"
#include <map>

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
        // Get sorted list of expressions
        std::list<BnfExpression> sortedExpressions = rule->expressions();
        sortedExpressions.sort(compare_expressions);

        // For each expression in sorted list
        for (std::list<BnfExpression>::iterator expression = sortedExpressions.begin();
             expression != sortedExpressions.end(); expression++)
        {
            //
            BnfExpression leftFactors;

            // Find longest common prefix
            for (std::vector<BnfTerm>::iterator term = expression->begin();
                 term != expression->end(); term++)
            {
                // If next expression has different starting term, start over
                // If common prefix is unique ignore
                // If more than one includ common prefix
                // Extract common prefix and create new rule (append N)
            }
        }
    }
}

std::list<BnfRule> BnfRule::leftFactor()
{
    // For each expression in sorted list
    for (BnfExpressionList::iterator outerExpr = m_Expressions.begin();
         outerExpr != m_Expressions.end(); outerExpr++)
    {
        BnfExpressionList exprs = m_Expressions;

        //prune initial non-matches
        for (BnfExpressionList::iterator innerExpr = exprs.begin();
             innerExpr != m_Expressions)

        for (int i = 0; i < outerExpr->size(); i++)
        {
            for (BnfExpressionList::iterator innerExpr = exprs.begin();
                 innerExpr != m_Expressions.end(); innerExpr++)
            {
                if ((*innerExpr)[i] != (*outerExpr)[i])
                    exprs.remove(*innerExpr);
            }
        }
    }
}

BnfRule::BnfRule()
{
}
