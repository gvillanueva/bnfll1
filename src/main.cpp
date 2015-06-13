#ifndef TEST
#include <fstream>
#include "bnflex.h"
#include "bnfsyn.h"
#include "bnfgrammar.h"

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
        BnfGrammar *grammar = syn.analyze(*tokens);
        grammar->connectNonTerminals();

        if (grammar) {
            std::cout << "Pass" << std::endl;
            grammar->print();
            grammar->leftFactor();
            grammar->print();
        }
        else
            std::cout << "Fail" << std::endl;
    }

    return 0;
}
#else
#include "bnfgrammar.h"
#include "bnfrule.h"
#include "bnfterm.h"

int main(int, char*[])
{
    BnfRule rule;
    rule.setRuleName("S");

    BnfRule rule2;
    rule2.setRuleName("E");

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

    BnfExpression expression5;
    expression5.push_back(Token("a", "TERM"));
    expression5.push_back(Token("b", "TERM"));

    rule.addExpression(expression4);
    rule.addExpression(expression2);
    rule.addExpression(expression1);

    rule2.addExpression(expression3);
    rule2.addExpression(expression5);

    BnfGrammar grammar;
    grammar.addRule(rule);
    grammar.addRule(rule2);
    grammar.print();
    grammar.leftFactor();
    grammar.print();
}

#endif
