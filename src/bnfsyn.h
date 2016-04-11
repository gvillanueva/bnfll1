/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/1/2015
 *              Modified, 6/14/2015
 * \ingroup     bnfll1
 * \file        bnfsyn.h
 *
 * \brief       Declares the structure of the Backus-Naur Form syntax analyzer
 *              class.
 */
#ifndef BNFSYN_H
#define BNFSYN_H

#include "token.h"
#include "bnfgrammar.h"

typedef std::vector<Token> TokenList;

/*!
 * \brief The syntax analyzer for the Backus-Naur Form parser.
 * The BnfSyn class is absolutely not thread-safe.
 */
class BnfSyn
{
public:
    /// Creates a new parser for the BNF language.
    BnfSyn();

    /// Analyzes the tokens from a BNF lexical analyzer.
    BnfGrammar* analyze(const TokenList* tokens);

private:
    /// The following methods implement the rules of the language
    bool syntax();
    bool rule();
    bool expression();
    bool lineEnd();
    bool list();
    bool term();
    bool literal();

    /// Returns whether the current token lexeme matches \p lexeme.
    bool readType(std::string type);

    /// Simplifies the code to add token to the current expression
    void addTokenToExpression(Token token, BnfExpression* expression);

    /// A reference to the beginning of our tokens list
    TokenList::const_iterator m_Iter;

    /// A reference to the end of our tokens list
    TokenList::const_iterator m_IterEnd;

    /// The BnfGrammar the parsed language produces.
    BnfGrammar* m_Grammar;

    /// The current rule being produced from the BNF input.
    BnfRule* m_CurrentRule;

    /// The current expression being produced from the BNF input.
    BnfExpression* m_CurrentExpression;
};

#endif // BNFSYN_H
