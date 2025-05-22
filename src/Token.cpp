

// Own
#include <Token.hpp>

Token::Token(const TokenType &type, const std::string &lexeme, const Value &literal, const int &line)
{
    _lexeme = lexeme;
    _line = line;
    _literal = literal;
    _type = type;
}

std::string Token::toString()
{
    return std::to_string(static_cast<int>(_type)) + " (" + _lexeme + ")";
}
