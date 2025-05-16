

#ifndef TOKEN_HPP
#define TOKEN_HPP

// Own
#include <TokenType.hpp>

// std
#include <string>

class Token
{
public:
    Token(const Token &other);
    Token(const TokenType &type, const std::string &lexeme, const int &line);

    Token &operator=(const Token &other);
    std::string toString();

    std::string lexeme() const;
    int line() const;
    TokenType type() const;

private:
    std::string _lexeme;
    int _line;
    // Object literal
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
inline TokenType Token::type() const
{
    return _type;
}

#endif