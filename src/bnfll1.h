#ifndef BNFLL1_H
#define BNFLL1_H

#include "bnfgrammar.h"
#include <set>
#include <vector>

class BnfRule;
class BnfTerm;

class BnfLl1
{
public:
    BnfLl1();
    std::vector<std::set<BnfRule*, BnfTerm>*> first(BnfGrammar* grammar);
    std::set<BnfRule*, BnfTerm>* first(BnfRule* rule);
};

#endif // BNFLL1_H
