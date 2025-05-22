

#ifndef TOKEN_HPP
#define TOKEN_HPP

// Own
#include <TokenType.hpp>
#include <Value.hpp>

// std
#include <string>

class Token
{
public:
    Token(const Token &other) = default;
    Token(const TokenType &type, const std::string &lexeme, const Value &literal, const int &line);

    Token &operator=(const Token &other) = default;
    std::string toString();

    std::string lexeme() const;
    int line() const;
    const Value &literal() const;
    TokenType type() const;

private:
    std::string _lexeme;
    int _line;
    Value _literal;
    TokenType _type;
};

inline std::string Token::lexeme() const
{
    return _lexeme;
}

inline int Token::line() const
{
    return _line;
}

inline const Value &Token::literal() const
{
    return _literal;
}

inline TokenType Token::type() const
{
    return _type;
}

#endif