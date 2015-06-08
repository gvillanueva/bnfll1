#include <fstream>
#include "bnflex.h"
#include "bnfsyn.h"

//Input:  Path to a file
//Output: An LL(1) table that could be used by a parser.
//Notes:  Does not produce a complete compiler, because it is missing a lexical
//        analyzer.
int main(int argc, char *argv[])
{
    BnfLex lex;
    BnfSyn syn;
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
        if (syn.analyze(*tokens))
            std::cout << "Pass" << std::endl;
        else
            std::cout << "Fail" << std::endl;
    }

    return 0;
}

