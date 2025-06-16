

// own
#include <BaseScanner.hpp>

char BaseScanner::advance()
{
    return source_[current_++];
}

bool BaseScanner::isAtEnd() const
{
    return current_ >= source_.length();
}

bool BaseScanner::match(const char &expected)
{
    if (isAtEnd() || source_[current_] != expected)
        return false;

    ++current_;
    return true;
}

void BaseScanner::newLine()
{
    ++line_;
}

char BaseScanner::peek() const
{
    return isAtEnd() ? '\0' : source_[current_];
}

char BaseScanner::peekNext() const
{
    return (current_ + 1 >= source_.length()) ? '\0' : source_[current_ + 1];
}