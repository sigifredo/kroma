

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token
{
public:
    enum TokenType
    {
        // Single character token
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        COMMA,
        DOT,
        MINUS,
        PLUS,
        SEMICOLON,
        SLASH,
        STAR,

        // One or two character token
        BANG,
        BANG_EQUAL,
        EQUAL,
        EQUAL_EQUAL,
        GREATER,
        GREATER_EQUAL,
        LESS,
        LESS_EQUAL,

        // Literals
        IDENTIFIER,
        STRING,
        NUMBER,

        // Keywords
        AND,
        CLASS,
        ELSE,
        FALSE,
        FUN,
        FOR,
        IF,
        _NULL,
        OR,
        PRINT,
        RETURN,
        SUPER,
        THIS,
        TRUE,
        VAR,
        WHILE,
        _EOF
    };

    Token(const TokenType &type, const std::string &lexeme, const int &line);

    std::string toString();

private:
    const TokenType type;
    const std::string lexeme;
    const int line;
};

#endif