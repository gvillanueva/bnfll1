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

bool BnfSyn::readType(std::string type)
{
    return (*m_Iter++).type() == type;
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
    if (readType("NONTERM"))
        if (readType("::="))
            if (expression())
                if (readType(";"))
                    return true;

    return false;
}

bool BnfSyn::expression()
{
    if (list()) {
        if (readType("|")) {
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
