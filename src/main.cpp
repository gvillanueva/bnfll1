#include <fstream>
#include "bnflex.h"
#include "bnfsyn.h"
#include "bnfgrammar.h"
#include "bnfll1.h"

//Input:  Path to a file
//Output: An LL(1) table that could be used by a parser.
//Notes:  Does not produce a complete compiler, because it is missing a lexical
//        analyzer.
int main(int argc, char *argv[])
{
    BnfLex lex;
    BnfSyn syn;
    BnfLl1 ll1;
    char *filename = NULL;

    // Ensure filename is defined
    if (argc < 2)
        return -1;

    filename = argv[1];
    std::ifstream stream(filename);
    TokenList *tokens = lex.analyze(stream, filename);

    /// Error checking of lexical analyzer??
    if (tokens->size() <= 0)
        return -2;
    else {
        BnfGrammar *grammar = syn.analyze(tokens);
        grammar->connectNonTerminals();

        if (grammar) {
            std::cout << "Pass" << std::endl;
            std::cout << "Before left factor" << std::endl;
            grammar->print();
            grammar->leftFactor();
            std::cout << std::endl << "After left factor" << std::endl;
            grammar->print();

            // Find first sets
            ll1.first(grammar);
            std::cout << std::endl << "First sets" << std::endl;
            ll1.printFirstSets();
        }
        else
            std::cout << "Fail" << std::endl;
    }

    return 0;
}
