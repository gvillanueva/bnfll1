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
#include "bnfsyn.h"

BnfSyn::BnfSyn()//const TokenList& tokens)
{
}

bool BnfSyn::analyze(const TokenList& tokens)
{
    m_Iter = tokens.begin();
    return syntax();
}

bool BnfSyn::readLexeme(std::string lexeme)
{
    return (*m_Iter).lexeme() == lexeme;
}

bool BnfSyn::syntax()
{
    if (rule()) {
        if (syntax())
            return true;
    }
    else
        return true;

    return false;
}

bool BnfSyn::rule()
{
    if (readLexeme("NONTERM"))
        if (readLexeme("::="))
            if (expression())
                if (readLexeme(";"))
                    return true;

    return false;
}

bool BnfSyn::expression()
{
    if (list()) {
        if (readLexeme("|")) {
            if (expression()) {
                return true;
            }

            //Must have an expression following a |
            return false;
        }

        // End of list of terms
        return true;
    }

    return false;
}

bool BnfSyn::list()
{
//    if (readLexeme("TERM") || readLexeme("NONTERM"))
//        if ()

    return false;
}

/// Convert EBNF to BNF
/// Remove Lambda productions
/// Remove unit productions
/// Left factor grammar
/// Generate LL(1) table
