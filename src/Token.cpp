

// own
#include <Token.hpp>

std::ostream &operator<<(std::ostream &os, const Token &token)
{
    os << "Token(";
    os << "type: " << static_cast<int>(token.type()) << ", ";
    os << "lexeme: \"" << token.lexeme() << "\", ";
    os << "literal: " << token.literal().toString();
    os << ", line: " << token.line();
    os << ")";

    return os;
}