#ifndef TEST
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
#else
#include "bnfrule.h"
#include "bnfterm.h"

int main(int, char*[])
{
    BnfRule rule;
    rule.setName("S");

    BnfExpression expression1;
    expression1.push_back(Token("if", "TERM"));
    expression1.push_back(Token("E", "NONTERM"));
    expression1.push_back(Token("then", "TERM"));
    expression1.push_back(Token("S", "NONTERM"));

    BnfExpression expression2;
    expression2.push_back(Token("if", "TERM"));
    expression2.push_back(Token("E", "NONTERM"));
    expression2.push_back(Token("then", "TERM"));
    expression2.push_back(Token("S", "NONTERM"));
    expression2.push_back(Token("else", "TERM"));
    expression2.push_back(Token("S", "NONTERM"));

    BnfExpression expression3;
    expression3.push_back(Token("a", "TERM"));

    BnfExpression expression4;
    expression4.push_back(Token("if", "TERM"));
    expression4.push_back(Token("E", "NONTERM"));
    expression4.push_back(Token("then", "TERM"));
    expression4.push_back(Token("S", "NONTERM"));
    expression4.push_back(Token("else", "TERM"));
    expression4.push_back(Token("Q", "NONTERM"));

    rule.addExpression(expression4);
    rule.addExpression(expression2);
    rule.addExpression(expression3);
    rule.addExpression(expression1);

    BnfGrammar grammar;
    grammar.addRule(rule);
    BnfGrammar leftFactored = grammar.leftFactor();
}

#endif
