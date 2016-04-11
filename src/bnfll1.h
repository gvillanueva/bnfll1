/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/12/2015
 *              Modified, 6/14/2015
 * \ingroup     bnfll1
 * \file        bnfll1.h
 *
 * \brief       Declares the structure of the Backus-Naur Form LL(1) parser
 *              generator.
 */
#ifndef BNFLL1_H
#define BNFLL1_H

#include "bnfgrammar.h"
#include <set>
#include <map>

// Forward-declarations
class BnfRule;
class BnfTerm;

/*!
 * \brief The BnfLl1 class uses a given grammar to produce the LL1 parsing table
 *        for an LL1 compiler.
 */
class BnfLl1
{
public:
    /// Instantiates a new LL(1) compiler generator.
    BnfLl1();

    /// Computes the first set from the given grammar.
    std::map<BnfRule*, std::set<std::string> >* first(BnfGrammar* grammar);

    /// Prints the result of the last first() operation.
    void printFirstSets();

private:
    /// Implements the first rule for generating a first set.
    void firstRule1(BnfRule* rule);

    /// Implements the second rule for generating a first set.
    void firstRule2(BnfRule* rule);

    /// Implements the third rule for generating a first set.
    void firstRule3(BnfRule* rule);

    /// Hold the working results of the first set computation.
    std::map<BnfRule*, std::set<std::string> >* m_FirstSets;
};

#endif // BNFLL1_H
