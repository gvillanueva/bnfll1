/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/1/2015
 *              Modified, 6/1/2015
 * \ingroup     bnfll1
 * \file        bnfsyn.cpp
 *
 * \brief       Defines the methods of the Backus-Naur Form syntax analyzer
 *              class.
 */
#include "bnfterm.h"
#include "bnfsyn.h"

BnfSyn::BnfSyn()
    :m_Grammar(0), m_CurrentRule(0), m_CurrentExpression(0)
{
}

BnfGrammar* BnfSyn::analyze(const TokenList& tokens)
{
    m_Iter = tokens.begin();
    m_IterEnd = tokens.end();
    m_Grammar = new BnfGrammar;

    if (syntax())
        return m_Grammar;// return grammar

    return NULL;
}

bool BnfSyn::readType(std::string type)
{
    if (m_Iter == m_IterEnd)
        return false;

    if (m_Iter->type() == type) {
        m_Iter++;
        return true;
    }

    return false;
}

bool BnfSyn::syntax()
{
    if (rule()) {
        syntax();
        return true;
    }

    return false;
}

bool BnfSyn::rule()
{
    if (readType("NONTERM"))
    {
        m_CurrentRule = new BnfRule;
        m_CurrentRule->setRuleName((m_Iter-1)->lexeme());
        if (m_Grammar->containsRuleName(m_CurrentRule->ruleName())) {
            delete m_CurrentRule;
            m_CurrentRule = 0;
            return false;
        }

        if (readType("::="))
            if (expression())
                if (readType(";")) {
                    m_Grammar->addRule(m_CurrentRule);
                    return true;
                }
    }

    return false;
}

bool BnfSyn::expression()
{
    m_CurrentExpression = new BnfExpression;

    if (list()) {
        if (readType("|")) {
            m_CurrentRule->addExpression(m_CurrentExpression);
            if (expression()) {
                return true;
            }

            //Must have an expression following a |
            return false;
        }

        m_CurrentRule->addExpression(m_CurrentExpression);
        // End of list of terms
        return true;
    }

    return false;
}

bool BnfSyn::list()
{
    if (term()) {
        addTokenToExpression(*(m_Iter-1), m_CurrentExpression);

        while (term()) {
            addTokenToExpression(*(m_Iter-1), m_CurrentExpression);
        }
        return true;
    }

    return false;
}

bool BnfSyn::term()
{
    return readType("TERM") || readType("NONTERM");
}

void BnfSyn::addTokenToExpression(Token token, BnfExpression* expression)
{
    // Don't add lambda
    // BnfRule will mark itself as nullable for empty expressions
    if (token.lexeme() == "?")
            return;

    if (token.type() == "NONTERM")
        expression->push_back(new BnfNonTerminal(token,
                              m_Grammar->findRuleByName(token.lexeme())));
    else
        expression->push_back(new BnfTerm(token));
}
