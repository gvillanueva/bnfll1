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
        return NULL;

    filename = argv[1];
    std::ifstream stream(filename);
    TokenList *tokens = lex.analyze(stream, filename);

    return 0;
}

