

// Own
#include <Token.hpp>

Token::Token(const TokenType &type, const std::string &lexeme, const int &line) : type(type),
                                                                                  line(line)
{
}

std::string Token::toString()
{
    return std::to_string(type) + lexeme;
}