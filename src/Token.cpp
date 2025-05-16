

// Own
#include <Token.hpp>

Token::Token(const Token &other)
{
    operator=(other);
}

Token::Token(const TokenType &type, const std::string &lexeme, const int &line)
{
    _lexeme = lexeme;
    _line = line;
    _type = type;
}

Token &Token::operator=(const Token &other)
{
    _lexeme = other._lexeme;
    _line = other._line;
    _type = other._type;

    return *this;
}

std::string Token::toString()
{
    return std::to_string(static_cast<int>(_type)) + " (" + _lexeme + ")";
}
