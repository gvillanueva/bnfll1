#include "bnfrule.h"
#include "bnfterm.h"
#include <algorithm>
#include <QDebug>

bool compare_expressions(BnfExpression* a, BnfExpression* b)
{
    if (a->size() < b->size())
        return true;
    else if (a->size() > b->size())
        return false;
    else
    {
        BnfExpression::iterator aIter = a->begin(), bIter = b->begin();
        while(aIter != a->end() && bIter != b->end())
            if ((*aIter)->token() != (*bIter)->token())
                return (*aIter)->token() < (*bIter)->token();
        return false;
    }
}

bool compare_terms(BnfTerm* a, BnfTerm* b)
{
    return a->token() == b->token();
}

BnfRule::BnfRule()
    :m_HasLambda(false)
{
    m_Expressions = new BnfExpressionVector;
    qDebug() << __func__ << m_RuleName.c_str();
}

BnfRule::BnfRule(const BnfRule& copy)
    :m_RuleName(copy.m_RuleName), m_Expressions(copy.m_Expressions),
     m_HasLambda(copy.m_HasLambda)
{
    qDebug() << __func__ << "copy" << m_RuleName.c_str();
}

BnfExpressionVector* BnfRule::expressions() const
{
    return m_Expressions;
}

void BnfRule::addExpression(BnfExpression* expression)
{
    if (expression->size())
        m_Expressions->push_back(expression);
    else if (!m_HasLambda)
    {
        BnfExpression* lambdaExpr = new BnfExpression;
        lambdaExpr->push_back(new BnfTerm(Token("λ", "TERM")));
        m_Expressions->push_back(lambdaExpr);
        m_HasLambda = true;
    }
}

std::string BnfRule::ruleName() const
{
    return m_RuleName;
}

void BnfRule::setRuleName(const std::string value)
{
    m_RuleName = value;
}

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
