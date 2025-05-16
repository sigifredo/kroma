

#ifndef SCANNER_HPP
#define SCANNER_HPP

// Own
#include <Token.hpp>

// std
#include <list>

class Scanner
{
public:
    Scanner(const std::string &src);

    std::list<Token> scanTokens();

private:
    std::string source;
    std::list<Token> tokens;
};

#endif