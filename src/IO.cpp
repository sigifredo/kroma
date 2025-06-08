

// own
#include <IO.hpp>

std::ostream &operator<<(std::ostream &os, const Token &token)
{
    os << token.toString();
    return os;
}