/*!
 * \author      Giancarlo Villanueva
 * \date        Created,  6/1/2015
 *              Modified, 6/1/2015
 * \ingroup     bnfll1
 * \file        token.h
 *
 * \brief       Declares the structure of the Token class.
 */
#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

/*!
 * \brief   The Token class contains a token's lexeme and type.
 */
class Token
{
public:
    /// Instantiates a Token object.
    Token(std::string lexeme, std::string type, std::string source = "",
          int line = 0, int column = 0);

    /// Instantiates a Token object using deep-copies of another Token's values.
    Token(const Token& copy);

    Token& operator=(const Token& copy);

    /// Gets the specific instance of the generic token type.
    std::string lexeme() const;

    /// Gets the token's generic type.
    std::string type() const;

    /// Gets the source file containing the token.
    std::string source() const;

    /// Gets the line of the source file where the token is found.
    int line() const;

    /// Gets the column of the source file where the token begins.
    int column() const;

private:
    /// The specific instance of the generic token type.
    std::string m_Lexeme;

    /// The type of token (identifier, preprocessor, etc).
    std::string m_Type;

    /// The source code file where the token exists.
    std::string m_Source;

    /// The line of the source code file where the token was found.
    int m_Line;

    /// The column of the source code file where the token begins.
    int m_Column;
};

#endif // TOKEN_H
