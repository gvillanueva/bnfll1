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
    m_IterEnd = tokens.end();
    return syntax();
}

bool BnfSyn::readType(std::string type)
{
    if (m_Iter == m_IterEnd)
        return false;

    if ((*m_Iter).type() == type) {
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
    if (term()) {
        while (term());
        return true;
    }

    return false;
}

bool BnfSyn::term()
{
    return readType("TERM") || readType("NONTERM");
}

/// Convert EBNF to BNF
/// Remove Lambda productions
/// Remove unit productions
/// Left factor grammar
/// Generate LL(1) table
