

#ifndef SCANNER_HPP
#define SCANNER_HPP

// Own
#include <Token.hpp>

// std
#include <list>

class Scanner
{
public:
    explicit Scanner(const std::string &src);
    std::list<Token> scanTokens();

private:
    std::string source;
    std::list<Token> tokens;

    size_t current;
    int line;

    char advance();
    void addToken(const TokenType &type, const std::string &lexeme);
    bool match(const char &expected);
    char peek() const;
    char peekNext() const;
    bool isAtEnd() const;

    void scanNumber(const char &firstDigit);
    void scanToken();
    void scanString(const char &delimiter);
};

#endif