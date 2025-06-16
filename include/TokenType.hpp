

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
    SEMICOLON,

    // Logical
    AND,
    OR,
    TRUE,
    FALSE,
    BANG,
    BANG_EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Math
    EQUAL,
    MINUS,
    PLUS,
    SLASH,
    STAR,

    // Literals
    IDENTIFIER,
    FSTRING,
    STRING,
    NUMBER,

    // Keywords
    CLASS,
    CONST,
    ELSE,
    _EOF,
    FOR,
    FUN,
    IF,
    LET,
    _NULL,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    WHILE,

    // Ranges
    DOT_DOT,
    BY,

    UNKNOWN
};

std::optional<TokenType> matchToken(const std::string &lexeme);

#endif