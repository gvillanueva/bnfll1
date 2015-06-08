/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/1/2015
 *              Modified, 6/8/2015
 * \ingroup     bnfll1
 * \file        bnflex.cpp
 *
 * \brief       Defines the methods of the Backus-Naur Form lexical analyzer
 *              class.
 */
#include "bnflex.h"
#include "token.h"
#include <stdio.h>
enum BNF_LEX_STATE
{
    START,

    NONTERMINAL_START,
    NONTERMINAL,

    ASSIGN1,
    ASSIGN2,

    TERMINAL,
    TERMINAL_ESCAPE
};

/*!
 * \brief Reads characters from input stream to form known tokens.
 * \param istream   An input stream to tokenize.
 * \param filename  Name of the file we may be parsing.
 * \return Pointer to a list of tokens found in the input stream.
 *
 * This function needs a populated symbol table to function correctly. You must
 * populate the table with keywords, if they exist.
 */
TokenList* BnfLex::analyze(std::istream &istream, const char *filename)
{
    BNF_LEX_STATE state = START;
    char ch  = 0;           /// Current symbol being parsed by the lexical analyzer
    int line = 1;           /// Tracks the current line position
    int linePosOffset = 0;  /// Tracks offset the current line
    int col = 0;

    std::string token;      /// Token being parsed
    //std::string error;      /// Error string
    TokenList *tokens = new TokenList;

    while (istream.get(ch) || token.length() && (ch = ' '))
    {
        switch (state)
        {
/// Start state
            case START:
                col = (int)istream.tellg() - linePosOffset;

                if (ch == '|')
                    tokens->push_back(Token("|", "|", filename, line, col));
                else if (ch == ';')
                    tokens->push_back(Token(";", ";", filename, line, col));
                else if (ch == '<')
                    state = NONTERMINAL_START;
                else if (ch == '"')
                    state = TERMINAL;
                else if (ch == ':')
                    state = ASSIGN1;
                else if (isspace(ch))
                {
                    /// Increment line counter on newlines
                    if (ch == '\n' || ch == '\r' || ch == '\f') {
                        line++;
                        linePosOffset = istream.tellg();
                    }
                    /// Otherwise ignore whitespace
                }
                else
                    printf("Unexpected '%c' encountered.\n", ch);
                break;
/// Non-terminal token
            case NONTERMINAL_START:
                if (isalpha(ch))
                {
                    token.push_back(ch);
                    state = NONTERMINAL;
                }
                else
                    printf("Expected a letter, got '%c'.\n", ch);
                break;
            case NONTERMINAL:
                if (ch == '>')
                {
                    tokens->push_back(Token(token, "NONTERM", filename, line, col));
                    token.clear();
                    state = START;
                }
                else if (isalpha(ch) || isdigit(ch) || ch == '_' || ch == '-')
                    token.push_back(ch);
                else
                    printf("Expected alphanumeric, '_', or '-' character, but got '%c'.\n", ch);
                break;
/// Multiple-character assignment operator
            case ASSIGN1:
                if (ch == ':')
                    state = ASSIGN2;
                else
                    printf("Expected ':', but got '%c'.\n", ch);
                break;
            case ASSIGN2:
                if (ch == '=')
                {
                    tokens->push_back(Token("::=", "::=", filename, line, col));
                    state = START;
                }
                else
                    printf("Expected '=', but got '%c'.\n", ch);
                break;
/// Terminal characters between "
            case TERMINAL:
                if (ch == '"')
                {
                    tokens->push_back(Token(token, "TERM", filename, line, col));
                    token.clear();
                    state = START;
                }
                else if (isprint(ch))
                {
                    if (ch == '\\')
                        state = TERMINAL_ESCAPE;
                    else
                        token.push_back(ch);
                }
                else
                    printf("Expected non-whitespace.");
                break;
            case TERMINAL_ESCAPE:
                if (ch == '\"')
                {
                    token.push_back(ch);
                    state = TERMINAL;
                }
                else
                    printf("Unrecognized escape character '%c'.\n", ch);
            break;
        }
    }
    /// It is an error if we're not in START when finished
    if (state != START)
        printf("Source code terminated mid-recognition.\n");

    return tokens;
}
