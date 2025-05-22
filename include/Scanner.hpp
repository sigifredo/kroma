

#ifndef SCANNER_HPP
#define SCANNER_HPP

// Own
#include <Token.hpp>

// std
#include <list>
#include <vector>

class Scanner
{
public:
    explicit Scanner(const std::string &src);
    std::vector<Token> scanTokens();

private:
    size_t current;
    int line;

    std::string source;
    std::list<Token> tokens;

    void addToken(const TokenType &type, const std::string &lexeme);
    char advance();
    bool isAtEnd() const;
    bool match(const char &expected);
    char peek() const;
    char peekNext() const;

    void scanIdentifier(const char &firstChar);
    void scanNumber(const char &firstDigit);
    void scanString(const char &delimiter);
    void scanToken();
};

#endif