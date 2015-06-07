#include "bnfsyn.h"

BnfSyn::BnfSyn()//const TokenList& tokens)
{
}



/// Convert EBNF to BNF
/// Remove Lambda productions
/// Remove unit productions
/// Left factor grammar
/// Generate LL(1) table
