

#ifndef BASESCANNER_HPP
#define BASESCANNER_HPP

// std
#include <string>

class BaseScanner
{
public:
    virtual ~BaseScanner() = default;

protected:
    size_t current;
    int line;
    std::string source;

    char advance();
    bool isAtEnd() const;
    bool match(const char &expected);
    char peek() const;
    char peekNext() const;
};

#endif