

#ifndef TOKENTYPE_HPP
#define TOKENTYPE_HPP

// std
#include <optional>
#include <string>

enum class TokenType
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
    _EOF,
    FALSE,
    FOR,
    FUN,
    IF,
    LET,
    _NULL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    WHILE,

    UNKNOWN
};

std::optional<TokenType> matchToken(const std::string &lexeme);

#endif