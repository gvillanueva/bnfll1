#include "bnfrule.h"
#include "bnfterm.h"
#include <algorithm>
#include <QDebug>

bool compare_expressions(const BnfExpression a, const BnfExpression b)
{
    return a > b;
}

BnfRule::BnfRule()
    :m_HasLambda(false)
{
    qDebug() << __func__ << m_RuleName.c_str();
}

BnfRule::BnfRule(const BnfRule& copy)
    :m_RuleName(copy.m_RuleName), m_Expressions(copy.m_Expressions),
     m_HasLambda(copy.m_HasLambda)
{
    qDebug() << __func__ << "copy" << m_RuleName.c_str();
}

BnfExpressionVector BnfRule::expressions() const
{
    return m_Expressions;
}

void BnfRule::addExpression(BnfExpression expression)
{
    if (expression.size())
        m_Expressions.push_back(expression);
    else if (!m_HasLambda)
    {
        BnfExpression lambdaExpr;
        lambdaExpr.push_back(Token("λ", "TERM"));
        m_Expressions.push_back(lambdaExpr);
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

std::vector<BnfRule>* BnfRule::leftFactor()
{
    // Sort expressions so that we don't have to worry that we didn't start with
    // the shortest common left factor
    std::sort(m_Expressions.begin(), m_Expressions.end());
    std::string nameSfx = "'";
    std::vector<BnfRule>* leftFactoredRules = new std::vector<BnfRule>;

    // For each expression in sorted vector
    for (BnfExpressionVector::iterator exprsIter = m_Expressions.begin();
         exprsIter != m_Expressions.end();)
    {
        bool leftFactored = false;
        BnfExpression::iterator firstLeft;

        std::pair<BnfExpression::iterator, BnfExpression::iterator> pair;

        // Produce new grammar rule
        BnfRule newRule;
        newRule.setRuleName(m_RuleName+nameSfx);

        // Start mismatching on next expression in the vector
        for (BnfExpressionVector::iterator otherExprs = exprsIter + 1;
             otherExprs != m_Expressions.end();)
        {
            // Hold the return value of mismatch for evaluation
            pair = std::mismatch(exprsIter->begin(), exprsIter->end(), otherExprs->begin());

            // If the second expressions's mismatched term is not its first term
            // The two expressions can be left factored
            if (pair.second != otherExprs->begin()) {
                firstLeft = pair.first;
                leftFactored = true;

                // If left factored, remove from original rule
                otherExprs->erase(otherExprs->begin(), pair.second);
                newRule.addExpression(*otherExprs);
                otherExprs = m_Expressions.erase(otherExprs);
            }
            // Since the expressions vector is sorted, we know we can break on
            // the first expression without a common left factor
            else
                break;
       }

        // If current expression was left factored, remove from original rule
        if (leftFactored)
        {
            BnfExpression leftFactored(exprsIter->begin(), firstLeft);
            leftFactored.push_back(Token(m_RuleName+nameSfx, "NONTERM"));
            m_Expressions.push_back(leftFactored);

            // Add right factors to new rule
            exprsIter->erase(exprsIter->begin(), firstLeft);
            newRule.addExpression(*exprsIter);
            leftFactoredRules->push_back(newRule);

            nameSfx += "'";
            exprsIter = m_Expressions.erase(exprsIter);
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



void BnfGrammar::leftFactor()
{
    // For each rule
    for (std::vector<BnfRule>::iterator rule = m_Rules.begin();
         rule != m_Rules.end(); rule++)
    {
        std::vector<BnfRule>* leftFactoredRules = rule->leftFactor();
        if (leftFactoredRules)
        {
            for (int i = 0; i < leftFactoredRules->size(); i++)
                rule = m_Rules.insert(rule+1, leftFactoredRules->at(i));
        }
    }
}

void BnfGrammar::addRule(BnfRule rule)
{
    m_Rules.push_back(rule);
}

void BnfGrammar::print()
{
    for (std::vector<BnfRule>::iterator rule = m_Rules.begin();
         rule != m_Rules.end(); rule++)
    {
        QDebug debugLine = qDebug();
        debugLine << rule->ruleName().c_str() << "->";

        for (std::vector<BnfExpression>::iterator expr = rule->m_Expressions.begin();
             expr != rule->m_Expressions.end(); expr++) {
            for (std::vector<BnfTerm>::iterator term = expr->begin();
                 term != expr->end(); term++){
                debugLine << term->m_Token.c_str();
            }
            if (expr+1 != rule->m_Expressions.end())
                debugLine << "|";
        }
    }
}
