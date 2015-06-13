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
        Token lastToken = *(m_Iter-1);
        if (lastToken.type() == "NONTERM")
            m_CurrentExpression->push_back(new BnfNonTerminal(lastToken,
                                m_Grammar->findRuleByName(lastToken.lexeme())));
        else
            m_CurrentExpression->push_back(new BnfTerm(lastToken));

        while (term()) {
            Token lastToken = *(m_Iter-1);
            if (lastToken.type() == "NONTERM")
                m_CurrentExpression->push_back(new BnfNonTerminal(lastToken,
                                    m_Grammar->findRuleByName(lastToken.lexeme())));
            else
                m_CurrentExpression->push_back(new BnfTerm(lastToken));
        }
        return true;
    }

    return false;
}

bool BnfSyn::term()
{
    return readType("TERM") || readType("NONTERM");
}

/// Convert EBNF to BNF
/// Remove Lambda productions?
/// Remove unit productions?
/// Generate LL(1) table
