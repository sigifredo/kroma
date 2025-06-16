

// own
#include <BaseScanner.hpp>

char BaseScanner::advance()
{
    return source[current++];
}

bool BaseScanner::isAtEnd() const
{
    return current >= source.length();
}

bool BaseScanner::match(const char &expected)
{
    if (isAtEnd() || source[current] != expected)
        return false;

    ++current;
    return true;
}

char BaseScanner::peek() const
{
    return isAtEnd() ? '\0' : source[current];
}

char BaseScanner::peekNext() const
{
    return (current + 1 >= source.length()) ? '\0' : source[current + 1];
}