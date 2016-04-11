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

/*!
 * \brief Creates a new parser for the BNF language.
 */
BnfSyn::BnfSyn()
    :m_Grammar(0), m_CurrentRule(0), m_CurrentExpression(0)
{
}

/*!
 * \brief Analyzes the tokens from a BNF lexical analyzer.
 * \param tokens The list of tokens from a lexical analyzer.
 * \return The generated grammar according to the input BNF language.
 */
BnfGrammar* BnfSyn::analyze(const TokenList* tokens)
{
    m_Iter = tokens->begin();
    m_IterEnd = tokens->end();
    m_Grammar = new BnfGrammar;

    if (syntax())
        return m_Grammar;// return grammar

    return NULL;
}

///////////////// Begin rules of the Backus-Naur Form language /////////////////

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

////////////////// End rules of the Backus-Naur Form language //////////////////

/*!
 * \brief Returns whether the current token type matches \p type.
 * \param lexeme The type to match against.
 * \return true if not at end of token list and \p type matches current token,
 *         otherwise false.
 */
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

/*!
 * \brief Simplifies the code to add token to the current expression
 * \param token The token to add to the expression
 * \param expression The expression to add the token to.
 *
 * If the current token is a lambda, we just skip it. If it is non-terminal, we
 * attempt to hook up it up with its rule.  This can be performed later by
 * BnfGrammar::connectNonTerminals() for non-terminals whose rules do not exist
 * at time of creation.
 */
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
