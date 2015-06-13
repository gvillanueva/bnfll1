#include "bnfll1.h"
#include "bnfterm.h"
#include "token.h"

BnfLl1::BnfLl1()
{
}

std::vector<std::pair<BnfRule*, std::set<BnfTerm*> > > BnfLl1::first(BnfGrammar* grammar)
{
    std::vector<std::pair<BnfRule*, std::set<BnfTerm*> > > firsts;
    std::vector<BnfRule*> rules = grammar->rules();
    for (std::vector<BnfRule*>::iterator rulesIter = rules.begin();
         rulesIter != rules.end(); rulesIter++)
    {
        firsts.push_back(std::pair<BnfRule*, std::set<BnfTerm*> > (
                             *rulesIter,
                             first(*rulesIter)));
    }

    return firsts;
}

std::set<BnfTerm*> BnfLl1::first(BnfRule* rule)
{
    std::set<BnfTerm*> firstSet;
    if (!rule)
        return firstSet;

    // For each expression
    for (BnfExpressionVector::iterator exprsIter = rule->expressions()->begin();
         exprsIter != rule->expressions()->end(); exprsIter++)
    {
        // Examine the first token in the expression
        if ((*(*exprsIter)->begin())->isTerm())
            firstSet.insert(*(*exprsIter)->begin());
        else
        {
            for (BnfExpression::iterator termsIter = (*exprsIter)->begin();
                 termsIter != (*exprsIter)->end(); termsIter++)
            {
                BnfNonTerminal* nonTerm = (BnfNonTerminal*)*termsIter;
                std::set<BnfTerm*> firsts = first(nonTerm->rule());
            }
        }
    }

    return firstSet;
}
