

// Own
#include <Token.hpp>

Token::Token(const TokenType &type, const std::string &lexeme, const int &line)
{
    _lexeme = lexeme;
    _line = line;
    _type = type;
}

std::string Token::toString()
{
    return std::to_string(static_cast<int>(_type)) + " (" + _lexeme + ")";
}
