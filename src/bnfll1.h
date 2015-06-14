#ifndef BNFLL1_H
#define BNFLL1_H

#include "bnfgrammar.h"
#include <set>
#include <vector>
#include <map>

class BnfRule;
class BnfTerm;

class BnfLl1
{
public:
    BnfLl1();
    std::map<BnfRule*, std::set<std::string> > first(BnfGrammar* grammar);
//    std::set<std::string> first(BnfRule* rule);
    void printFirstSets();

private:
    void firstRule1(BnfRule* rule);
    void firstRule2(BnfRule* rule);
    void firstRule3(BnfRule* rule);

    std::map<BnfRule*, std::set<std::string> > m_FirstSets;
    std::map<BnfRule*, bool> m_FinishedRule3;
};

#endif // BNFLL1_H
